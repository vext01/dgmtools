#include <stdio.h>
#include <stdlib.h>

#include "rom.h"
#include "../include/dgm_common.h"

int
main(int argc, char **argv)
{
	struct gns_rom_header		hdr;

	if (argc != 2) {
		fprintf(stderr, "usage XXX\n");
		exit(EXIT_FAILURE);
	}

	if (gns_load_rom_header(&hdr, argv[1]) != DGM_OK) {
		fprintf(stderr, "load header failed XXX\n");
		exit(EXIT_FAILURE);
	}

	gns_print_rom_header(&hdr);

	exit(EXIT_SUCCESS);
}
