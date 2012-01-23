#include <stdio.h>
#include <stdlib.h>

#include "dgenmen.h"
#include "rom.h"

int
main(int argc, char **argv)
{
	struct gns_rom_header		hdr;

	if (argc != 2) {
		fprintf(stderr, "usage XXX\n");
		exit(EXIT_FAILURE);
	}

	if (gns_load_rom_header(&hdr, argv[1]) != GNS_OK) {
		fprintf(stderr, "load header failed XXX\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
