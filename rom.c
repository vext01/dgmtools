#include <stdio.h>

#include "dgenmen.h"
#include "rom.h"

struct gns_rom_header_mapping gns_rom_header_mappings[] = {
	{GNS_OFS_CONSOLE_NAME,	GNS_FLEN_CONSOLE_NAME,	"Console Name"},
	{GNS_OFS_COPYRIGHT,	GNS_FLEN_COPYRIGHT,	"Copyright"},
	{GNS_OFS_GAME_NAME_DOMESTIC, GNS_FLEN_GAME_NAME_DOMESTIC, "Domestic Name"},
	{GNS_OFS_GAME_NAME_OVERSEAS, GNS_FLEN_GAME_NAME_OVERSEAS, "Overseas Name"},
	{GNS_OFS_TYPE,		GNS_FLEN_TYPE,		"Game Type"},
	{GNS_OFS_PRODUCT_CODE,	GNS_FLEN_PRODUCT_CODE,	"Product Code"},
	{GNS_OFS_CHECKSUM,	GNS_FLEN_CHECKSUM,	"Checksum"},
	{GNS_OFS_IO_SUPPORT,	GNS_FLEN_IO_SUPPORT,	"IO Support"},
	{GNS_OFS_ROM_CAPACITY,	GNS_FLEN_ROM_CAPACITY,	"ROM Capacity"},
	{GNS_OFS_RAM,		GNS_FLEN_RAM,		"RAM"},
	{GNS_OFS_MODEM_DATA,	GNS_FLEN_MODEM_DATA,	"Modem Data"},
	{GNS_OFS_MEMO,		GNS_FLEN_MEMO,		"Memo"},
	{GNS_OFS_RELEASE_COUNTRY, GNS_FLEN_RELEASE_COUNTRY, "Release Country"},
	{-1,			-1,			0}
};



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
	GNS_PRINT_HDR_FLD("Console Name", hdr->game_name_domestic, GNS_FLEN_GAME_NAME_DOMESTIC);
	GNS_PRINT_HDR_FLD("Game Name (domestic)", hdr->game_name_domestic, GNS_FLEN_GAME_NAME_DOMESTIC);
	GNS_PRINT_HDR_FLD("Game Name (overseas)", hdr->game_name_overseas, GNS_FLEN_GAME_NAME_OVERSEAS);
}
