#include <stdio.h>
#include <string.h>

#include "fis.h"
#include "ahci.h"

void debug_FIS_REG_H2D(FIS_REG_H2D *ptr) {
	printf("---debug_FIS_REG_H2D---\n");
	printf("fis_type %x\n", ptr->fis_type);
	printf("c %x\n", ptr->c);
	printf("command %x\n", ptr->command);
	printf("lba0 %x\n", ptr->lba0);
	printf("lba1 %x\n", ptr->lba1);
	printf("lba2 %x\n", ptr->lba2);
	printf("device %x\n", ptr->device);
	printf("lba3 %x\n", ptr->lba3);
	printf("lba4 %x\n", ptr->lba4);
	printf("lba5 %x\n", ptr->lba5);
	printf("countl %x counth %x\n", ptr->countl, ptr->counth);
	printf("------\n");
}

void debug_FIS_REG_D2H(volatile FIS_REG_D2H *ptr) {
	printf("---debug_FIS_REG_D2H---\n");
	printf("fis_type %x\n", ptr->fis_type);
	printf("i %x\n", ptr->i);
	printf("status %x\n", ptr->status);
	printf("lba0 %x\n", ptr->lba0);
	printf("lba1 %x\n", ptr->lba1);
	printf("lba2 %x\n", ptr->lba2);
	printf("device %x\n", ptr->device);
	printf("lba3 %x\n", ptr->lba3);
	printf("lba4 %x\n", ptr->lba4);
	printf("lba5 %x\n", ptr->lba5);
	printf("countl %x counth %x\n", ptr->countl, ptr->counth);
	printf("------\n");
}

void debug_FIS_DATA(FIS_DATA *ptr) {
	printf("---debug_FIS_DATA---\n");
	printf("fis_type %x\n", ptr->fis_type);
	printf("data %x\n", ptr->data[0]);
	printf("------\n");
}

void debug_FIS_PIO_SETUP(volatile FIS_PIO_SETUP *ptr) {
	printf("---FIS_PIO_SETUP---\n");
	printf("fis_type %x\n", ptr->fis_type);
	printf("d %x i %x\n", ptr->d, ptr->i);
	printf("status %x\n", ptr->status);
	printf("lba0 %x\n", ptr->lba0);
	printf("lba1 %x\n", ptr->lba1);
	printf("lba2 %x\n", ptr->lba2);
	printf("device %x\n", ptr->device);
	printf("lba3 %x\n", ptr->lba3);
	printf("lba4 %x\n", ptr->lba4);
	printf("lba5 %x\n", ptr->lba5);
	printf("countl %x counth %x\n", ptr->countl, ptr->counth);
	printf("------\n");
}

void debug_FIS_DMA_SETUP(volatile FIS_DMA_SETUP *ptr) {
	printf("---FIS_DMA_SETUP---\n");
	// TODO
	printf("------\n");
}

/*
void init_FIS_TYPE_REG_H2D(FIS_REG_H2D *fis) {
	memset(&fis, 0, sizeof(FIS_REG_H2D));
	fis->fis_type = FIS_TYPE_REG_H2D;
	// TODO 
}
*/