/*
 * Copyright (c) 2012, Edd Barrett <vext01@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>

#include "rom.h"
#include "../include/dgm_common.h"

struct gns_rom_header_mapping gns_rom_header_mappings[] = {
	{GNS_OFS_CONSOLE,	GNS_FLEN_CONSOLE,	"Console Name",	gns_print_rom_header_field_char},
	{GNS_OFS_COPYRIGHT,	GNS_FLEN_COPYRIGHT,	"Copyright",	gns_print_rom_header_field_char},
	{GNS_OFS_NAME_DOMESTIC, GNS_FLEN_NAME_DOMESTIC, "Domestic Name",gns_print_rom_header_field_char},
	{GNS_OFS_NAME_OVERSEAS, GNS_FLEN_NAME_OVERSEAS, "Overseas Name",gns_print_rom_header_field_char},
	{GNS_OFS_TYPE,		GNS_FLEN_TYPE,		"Game Type",	gns_print_rom_header_field_char},
	{GNS_OFS_PRODUCT_CODE,	GNS_FLEN_PRODUCT_CODE,	"Product Code",	gns_print_rom_header_field_char},
	{GNS_OFS_CHECKSUM,	GNS_FLEN_CHECKSUM,	"Checksum",	gns_print_rom_header_field_hex},
	{GNS_OFS_IO_SUPPORT,	GNS_FLEN_IO_SUPPORT,	"IO Support",	gns_print_rom_header_field_char},
	{GNS_OFS_CAPACITY,	GNS_FLEN_CAPACITY,	"ROM Capacity",	gns_print_rom_header_field_hex},
	{GNS_OFS_RAM,		GNS_FLEN_RAM,		"RAM",		gns_print_rom_header_field_hex},
	{GNS_OFS_RAM_PRESENT,	GNS_FLEN_RAM_PRESENT,	"RAM Present?",	gns_print_rom_header_field_char},
	{GNS_OFS_RAM_START,	GNS_FLEN_RAM_START,	"RAM Start",	gns_print_rom_header_field_u32_byteswapped},
	{GNS_OFS_RAM_LENGTH,	GNS_FLEN_RAM_LENGTH,	"RAM Length",	gns_print_rom_header_field_u32_byteswapped},
	{GNS_OFS_MODEM_DATA,	GNS_FLEN_MODEM_DATA,	"Modem Data",	gns_print_rom_header_field_char},
	{GNS_OFS_MEMO,		GNS_FLEN_MEMO,		"Memo",		gns_print_rom_header_field_char},
	{GNS_OFS_COUNTRY,	GNS_FLEN_COUNTRY,	"Release Country",gns_print_rom_header_field_char},
	{-1,			-1,			0,		NULL}
};

int
gns_load_rom_header(struct gns_rom_header *hdr, char *file)
{
	FILE			*f;
	int			 ret = DGM_FAIL;

	if ((f = fopen(file, "r")) == NULL) {
		warn("fopen");
		goto clean;
	}

	printf("Loading %d bytes from %s\n", sizeof(struct gns_rom_header), file);
	if (fread(hdr, sizeof(struct gns_rom_header), 1, f) != 1) {
		warn("fread: short read");
		goto clean;
	}

	ret = DGM_OK;
clean:
	fclose(f);
	return (ret);
}

/*
 * Fields in the rom are not null terminated, so we have to print them like this
 */
void
gns_print_rom_header_field_char(char *title, void *data, size_t ct)
{
	int			 i;
	char			*str = (char *) data;

	printf("%-30s: [", title);					\
	for (i = 0; i < ct; i++)
		putchar(str[i]);
	puts("]");
}

void
gns_print_rom_header_field_hex(char *title, void *data, size_t ct)
{
	int			 i;
	unsigned char		*bytes = (unsigned char *) data;

	printf("%-30s: ", title);					\
	for (i = 0; i < ct; i++)
		printf("%02x ", bytes[i]);
	puts("");
}

void
gns_print_rom_header_field_u32_byteswapped(char *title, void *data, size_t ct)
{
	uint32_t		val = 0;
	int			i;

	unsigned char		*bytes = (unsigned char *) data;
	printf("%-30s: ", title);					\
	for (i = 0; i < ct; i++)
		printf("%02x ", bytes[i]);
	puts("");

	if (ct != 4) {
		warn("expected a 4 byte count");
		return;
	}

	val += ((uint8_t *) data)[0] << 16;
	val += ((uint8_t *) data)[1] << 24;
	val += ((uint8_t *) data)[2] << 0;
	val += ((uint8_t *) data)[3] << 8;

	printf("%-30s: 0x%4x\n", title, val);
}

void
gns_print_rom_header(struct gns_rom_header *hdr)
{
	struct gns_rom_header_mapping		*f = gns_rom_header_mappings;
	void					*fld_start;

	while (f->name != NULL) {
		fld_start = (void *) hdr + f->offset;
		f->printer(f->name, fld_start, f->length);
		f++;
	}
}
