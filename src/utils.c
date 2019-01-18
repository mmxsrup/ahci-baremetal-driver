#include "stdio.h"
#include <stdint.h>

#include "utils.h"


// Find a free command list slot
int find_cmdslot(HBA_PORT *port) {
	// If not set in SACT and CI, the slot is free
	uint32_t slots = (port->sact | port->ci);
	for (int i = 0; i < 32; i++) {
		if ((slots & 1) == 0) return i;
		slots >>= 1;
	}
	printf("Cannot find free command list entry\n");
	return -1;
}
