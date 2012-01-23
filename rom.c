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
	if (fread(hdr, sizeof(struct gns_rom_header), 1, f) != 1) {
		warn("fread: short read");
		goto clean;
	}

	ret = GNS_OK;
clean:
	fclose(f);
	return (ret);
}

/*
 * Fields in the rom are not null terminated, so we have to print them like this
 */
void
gns_nprint(char *str, size_t ct)
{
	int			i;

	for (i = 0; i < ct; i++)
		putchar(str[i]);
}

#define GNS_PRINT_HDR_FLD(title, field, len)				\
	printf("%-30s: [", title);					\
	gns_nprint(field, len);						\
	puts("]");
void
gns_print_rom_header(struct gns_rom_header *hdr)
{
	GNS_PRINT_HDR_FLD("Game Name (domestic)", hdr->game_name_domestic, GNS_FLEN_GAME_NAME_DOMESTIC);
	GNS_PRINT_HDR_FLD("Game Name (overseas)", hdr->game_name_overseas, GNS_FLEN_GAME_NAME_OVERSEAS);
}
