#include <stdio.h>

#include "dgenmen.h"
#include "rom.h"

int
gns_load_rom_header(struct gns_rom_header *hdr, char *file)
{
	FILE			*f;
	int			 ret = GNS_FAIL;

	if ((f = fopen(file, "r")) == NULL) {
		warn("fopen");
		goto clean;
	}

	printf("Loading %d bytes from %s\n", sizeof(struct gns_rom_header), file);
	if ((fread(hdr, sizeof(struct gns_rom_header), 1, f))
	    != sizeof(struct gns_rom_header)) {
		warn("fread");
		goto clean;
	}

	ret = GNS_OK;
clean:
	fclose(f);
	return (ret);
}

void
gns_print_rom_header(struct gns_rom_header *hdr)
{
}
