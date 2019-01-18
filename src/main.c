#include <stdio.h>

#include "fis.h"
#include "ahci.h"
#include "read.h"
#include "write.h"

#define HBA_MEM_BASE_ADDRESS 0xFD0C0000

#define H2D_DATA_BASE_ADDRESS 0x1000000 // host to data を格納するアドレス
#define D2H_DATA_BASE_ADDRESS 0x1000000 // data to host を格納するアドレス

#define PORT_NUM 0

void testRead(HBA_MEM *ptr) {
	// 2018セクタをオフセット0~2017から読み込む, 512*2018 = 1M
	int result = sata_read(&(ptr->ports[PORT_NUM]), 0, 15, 16, (uint16_t*)D2H_DATA_BASE_ADDRESS);
	if (result) printf("testRead Success\n");
	else printf("test Read Error\n");
}

void testWrite(HBA_MEM *ptr) {
	int result = sata_write(&(ptr->ports[1]), 0, 2017, 2018, (uint16_t*)H2D_DATA_BASE_ADDRESS);
	if (result) printf("testWrite Success\n");
	else printf("testWrite Error\n");
}


void setup(HBA_MEM* ptr) {

	// sata clock program
	ptr->pctrl = 0x010200;

	// axis bus setup 
	ptr->paxic = 0x1;

	/* Port Phy Cfg register enables */
	ptr->pcfg = 0x2;

	/* Phy Control OOB timing parameters COMINIT */
	ptr->pp2c = 0x28184616;

	/* Phy Control OOB timing parameters COMWAKE */
	ptr->pp3c = 0x13081907;

	/* Phy Control Burst timing setting */
	ptr->pp4c = 0x064A0815;

	/* Rate Change Timer and Retry Interval Timer setting */
	ptr->pp5c = (0xB00 << 20);

	ptr->ports[0].sctl = (0x33 << 4);
	ptr->ports[0].serr = 0xffffffff;
}


int main(void) {
	HBA_MEM* hba_mem_ptr = (HBA_MEM*)HBA_MEM_BASE_ADDRESS;

	setup(hba_mem_ptr);
	hba_mem_ptr->ports[PORT_NUM].clb = 0x2000000;
	hba_mem_ptr->ports[PORT_NUM].fb  = 0x3000000;

	hba_mem_ptr->ports[PORT_NUM].cmd = (1 << 4);
	while ((hba_mem_ptr->ports[PORT_NUM].cmd & ((1<<15))) == 0);
	hba_mem_ptr->ports[PORT_NUM].cmd = 1;

	debug_HBA_MEM(hba_mem_ptr);
	testRead(hba_mem_ptr);
}