#include <stdio.h>

#include "ahci.h"
#include "fis.h"

void debug_HBA_PORT(HBA_PORT *ptr) {
	printf("---debug_HBA_PORT---\n");
	printf("command list base address %x %x\n", ptr->clbu, ptr->clb);
	printf("FIS base address %x %x\n", ptr->fbu, ptr->fb);
	printf("interrupt status %x\n", ptr->is);
	printf("interrupt enable %x\n", ptr->ie);
	printf("commnad ans status %x\n", ptr->cmd);
	printf("commnad issue\n", ptr->ci);
	printf("------\n");
}

void debug_HBA_MEM(HBA_MEM *ptr) {
	printf("---debug_HBA_MEM---\n");
	printf("hport[0] addr %p\n", &(ptr->ports[0]));
	printf("hport[1] addr %p\n", &(ptr->ports[1]));
	printf("------\n");
}

void debug_HBA_CMD_HEADER(HBA_CMD_HEADER *ptr) {
	printf("---debug_HBA_CMD_HEADER---\n");
	printf("Command FIS length %x\n", ptr->cfl);
	printf("w %x\n", ptr->w);
	printf("prdt length\n", ptr->prdtl);
	printf("Command table base addr %x %x\n", ptr->ctbau, ptr->ctba);
	printf("------\n");
}

void debug_HBA_FIS(HBA_FIS *ptr) {
	printf("---debug_HBA_FIS---\n");
	debug_FIS_DMA_SETUP(&(ptr->dsfis));
	debug_FIS_PIO_SETUP(&(ptr->psfis));
	debug_FIS_REG_D2H(&(ptr->rfis));
	// debug_FIS_DEV_BITS(&(ptr->sdafis));
	printf("------\n");
}

void debug_HBA_PRDT_ENTRY(HBA_PRDT_ENTRY *ptr) {
	printf("---debug_HBA_PRDT_ENTRY---\n");
	printf("Data base address %x %x\n", ptr->dbau, ptr->dba);
	printf("Byte Count %x\n", ptr->dbc);
	printf("i %x\n", ptr->i);
	printf("------\n");	
}

void debug_HBA_CMD_TBL(HBA_CMD_TBL *ptr) {
	printf("---debug_HBA_CMD_TBL---\n");
	// TODO: cfis[64]
	debug_HBA_CMD_TBL(ptr);
	printf("------\n");
}