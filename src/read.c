#include <stdio.h>
#include <string.h>

#include "ahci.h"
#include "fis.h"
#include "utils.h"

#define ATA_DEV_BUSY 0x80
#define ATA_DEV_DRQ 0x08


/*
 * "count" 分のセクタを "starth:startl" が指すオフセットから読み取り、"buf" へ書き込む
 * count * 512 byteを読み込める
 * 各PRDで8kb読み込めるようにするので, 一つのPRDで16セクタ
 * prdtl =  floor((count - 1) / 16) + 1
 * 簡略化するために count == 0 (MOD 16)とすることで prdtl = count / 16;
 */
int sata_read(HBA_PORT *port, uint32_t startl, uint32_t starth, uint32_t count, uint16_t *buf)
{
	port->is = (uint32_t) -1;		// Clear pending interrupt bits 割り込みステータスフラグをすべてクリアする
 	int slot = find_cmdslot(port);
 	if (slot == -1)
		return 0;
 
	HBA_CMD_HEADER *cmdheader = (HBA_CMD_HEADER*)port->clb;
	cmdheader += slot;
	cmdheader->cfl = sizeof(FIS_REG_H2D)/sizeof(uint32_t);	// Command FIS size
	cmdheader->w = 0;		// Read from device
	cmdheader->prdtl = count / 16;
 
	HBA_CMD_TBL *cmdtbl = (HBA_CMD_TBL*)(cmdheader->ctba);
	memset(cmdtbl, 0, sizeof(HBA_CMD_TBL) + (cmdheader->prdtl-1)*sizeof(HBA_PRDT_ENTRY));
 

	// 8K bytes (16 sectors) per PRDT
	for (int i = 0; i < cmdheader->prdtl; i++) {
		cmdtbl->prdt_entry[i].dba = (uint32_t)buf;
		cmdtbl->prdt_entry[i].dbc = 8*1024-1;	// 8K bytes (this value should always be set to 1 less than the actual value)
		cmdtbl->prdt_entry[i].i = 1;
		buf += 4*1024;	// 4K words
		count -= 16;	// 16 sectors
	}

	if (count != 0) {
		printf("[ERROR] ptrd count\n");
		return 0;
	}
 

	// Setup command
	FIS_REG_H2D *cmdfis = (FIS_REG_H2D*)(&cmdtbl->cfis);
 
	cmdfis->fis_type = FIS_TYPE_REG_H2D;
	cmdfis->c = 1;	// Command
	cmdfis->command = ATA_CMD_READ_DMA_EX;
 
	cmdfis->lba0 = (uint8_t)startl;
	cmdfis->lba1 = (uint8_t)(startl>>8);
	cmdfis->lba2 = (uint8_t)(startl>>16);
	cmdfis->device = 1<<6;	// LBA mode
 
	cmdfis->lba3 = (uint8_t)(startl>>24);
	cmdfis->lba4 = (uint8_t)starth;
	cmdfis->lba5 = (uint8_t)(starth>>8);
 
	cmdfis->countl = count & 0xFF;
	cmdfis->counth = (count >> 8) & 0xFF;
 
	// The below loop waits until the port is no longer busy before issuing a new command
	int spin = 0; // Spin lock timeout counter
	while ((port->tfd & (ATA_DEV_BUSY | ATA_DEV_DRQ)) && spin < 1000000) {
		spin++;
	}
	if (spin == 1000000) {
		printf("Port is hung\n");
		return 0;
	}
 
	port->ci = (1<<slot);	// Issue command
 
	// Wait for completion
	while (1)
	{
		// In some longer duration reads, it may be helpful to spin on the DPS bit 
		// in the PxIS port field as well (1 << 5)
		if ((port->ci & (1<<slot)) == 0) break;
		/*
		if (port->is & HBA_PxIS_TFES)	// Task file error
		{
			trace_ahci("Read disk error\n");
			return FALSE;
		}
		*/
	}
 
 /*
	// Check again
	if (port->is & HBA_PxIS_TFES)
	{
		trace_ahci("Read disk error\n");
		return FALSE;
	}
*/
 
	return 1;
}
 