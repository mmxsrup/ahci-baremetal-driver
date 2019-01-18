#ifndef INCLUDE_READ
#define INCLUDE_READ

int sata_read(HBA_PORT *port, uint32_t startl, uint32_t starth, uint32_t count, uint16_t *buf);

#endif

