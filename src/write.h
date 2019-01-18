#ifndef INCLUDE_WRITE
#define INCLUDE_WRITE

int sata_write(HBA_PORT *port, uint32_t startl, uint32_t starth, uint32_t count, uint16_t *buf);

#endif

