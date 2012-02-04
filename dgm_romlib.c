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

#include <sys/types.h>
#include <sys/stat.h>

#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include "dgm_romlib.h"
#include "dgm_common.h"

struct dgm_rom_header_mapping dgm_rom_header_mappings[] = {
	{GNS_OFS_CONSOLE,	GNS_FLEN_CONSOLE,	"Console Name",	dgm_print_rom_header_field_char},
	{GNS_OFS_COPYRIGHT,	GNS_FLEN_COPYRIGHT,	"Copyright",	dgm_print_rom_header_field_char},
	{GNS_OFS_NAME_DOMESTIC, GNS_FLEN_NAME_DOMESTIC, "Domestic Name",dgm_print_rom_header_field_char},
	{GNS_OFS_NAME_OVERSEAS, GNS_FLEN_NAME_OVERSEAS, "Overseas Name",dgm_print_rom_header_field_char},
	{GNS_OFS_TYPE,		GNS_FLEN_TYPE,		"Game Type",	dgm_print_rom_header_field_char},
	{GNS_OFS_PRODUCT_CODE,	GNS_FLEN_PRODUCT_CODE,	"Product Code",	dgm_print_rom_header_field_char},
	{GNS_OFS_CHECKSUM,	GNS_FLEN_CHECKSUM,	"Checksum",	dgm_print_rom_header_field_hex},
	{GNS_OFS_IO_SUPPORT,	GNS_FLEN_IO_SUPPORT,	"IO Support",	dgm_print_rom_header_field_char},
	{GNS_OFS_CAPACITY,	GNS_FLEN_CAPACITY,	"ROM Capacity",	dgm_print_rom_header_field_hex},
	{GNS_OFS_RAM,		GNS_FLEN_RAM,		"RAM",		dgm_print_rom_header_field_hex},
	{GNS_OFS_RAM_PRESENT,	GNS_FLEN_RAM_PRESENT,	"RAM Present?",	dgm_print_rom_header_field_char},
	{GNS_OFS_RAM_START,	GNS_FLEN_RAM_START,	"RAM Start",	dgm_print_rom_header_field_u32_byteswapped},
	{GNS_OFS_RAM_END,	GNS_FLEN_RAM_END,	"RAM End",	dgm_print_rom_header_field_u32_byteswapped},
	{GNS_OFS_MODEM_DATA,	GNS_FLEN_MODEM_DATA,	"Modem Data",	dgm_print_rom_header_field_char},
	{GNS_OFS_MEMO,		GNS_FLEN_MEMO,		"Memo",		dgm_print_rom_header_field_char},
	{GNS_OFS_COUNTRY,	GNS_FLEN_COUNTRY,	"Release Country",dgm_print_rom_header_field_char},
	{-1,			-1,			0,		NULL}
};

int
dgm_load_rom_header(struct dgm_rom_header *hdr, char *file)
{
	FILE			*f;
	int			 ret = DGM_FAIL;

	DPRINTF(HGD_D_INFO, "load %s", file);

	if ((f = fopen(file, "r")) == NULL) {
		warn("fopen");
		goto clean;
	}

	if (fread(hdr, sizeof(struct dgm_rom_header), 1, f) != 1) {
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
dgm_print_rom_header_field_char(char *title, void *data, size_t ct)
{
	int			 i;
	char			*str = (char *) data;

	printf("%-30s: [", title);					\
	for (i = 0; i < ct; i++)
		putchar(str[i]);
	puts("]");
}

void
dgm_print_rom_header_field_hex(char *title, void *data, size_t ct)
{
	int			 i;
	unsigned char		*bytes = (unsigned char *) data;

	printf("%-30s: ", title);					\
	for (i = 0; i < ct; i++)
		printf("%02x ", bytes[i]);
	puts("");
}

void
dgm_print_rom_header_field_u32_byteswapped(char *title, void *data, size_t ct)
{
	uint32_t		val = 0;

	if (ct != 4) {
		warn("expected a 4 byte count");
		return;
	}

	val |= ((uint8_t *) data)[1] << 16;
	val |= ((uint8_t *) data)[0] << 24;
	val |= ((uint8_t *) data)[3] << 0;
	val |= ((uint8_t *) data)[2] << 8;

	printf("%-30s: 0x%4x\n", title, val);
}

void
dgm_print_rom_header(struct dgm_rom_header *hdr)
{
	struct dgm_rom_header_mapping		*f = dgm_rom_header_mappings;
	void					*fld_start;

	while (f->name != NULL) {
		fld_start = (void *) hdr + f->offset;
		f->printer(f->name, fld_start, f->length);
		f++;
	}
}

/*
 * Load and unpad a dgen-sdl ram dump file into a buffer.
 *
 * dgen-sdl dumps every byte of a ram save in a word aligned
 * fashion, which is not true to the megadrive.
 */
int
dgm_dgen_ram_unpad(struct dgm_file *in_fs, struct dgm_file *out_fs)
{
	int			 ret = DGM_FAIL;
	size_t			 i;
	unsigned char		*p;

	DPRINTF(HGD_D_INFO, "unpadding %lu bytes", in_fs->sz);
	DPRINTF(HGD_D_INFO, "allocd %lu bytes", in_fs->sz/2);

	if ((out_fs->bytes = malloc(in_fs->sz / 2)) == NULL) {
		warn("malloc");
		goto clean;
	}
	out_fs->sz = 0;

	memset(out_fs->bytes, 0, sizeof(in_fs->sz / 2));

	p = out_fs->bytes;
	for (i = 0; i < in_fs->sz; i+=2) {
		*(p++) = in_fs->bytes[i];
		out_fs->sz++;
	}

	DPRINTF(HGD_D_INFO, "unpad done");
	ret = DGM_OK;
clean:
	return (ret);
}

int
dgm_dgen_ram_pad(struct dgm_file *in_fs, struct dgm_file *out_fs)
{
	int			 ret = DGM_FAIL;
	size_t			 i;
	unsigned char		*p;

	DPRINTF(HGD_D_INFO, "padding %lu bytes", in_fs->sz);

	memset(out_fs, 0, sizeof(*out_fs));

	if ((out_fs->bytes = calloc(2, in_fs->sz)) == NULL) {
		warn("calloc");
		goto clean;
	}

	p = out_fs->bytes;
	for (i = 0; i < in_fs->sz; i++) {
		*(p++) = in_fs->bytes[i];
		*(p++) = 0x00;
		out_fs->sz += 2;
	}

	DPRINTF(HGD_D_INFO, "Padding OK");
	ret = DGM_OK;
clean:
	return (ret);
}

int
dgm_suck_in_file(char *path, struct dgm_file *fs)
{
	FILE			*f = NULL;
	int			 c, ret = DGM_FAIL;
	struct stat		 st;
	unsigned char		*p;

	memset(fs, 0, sizeof(*fs));

	if (stat(path, &st) < 0) {
		warn("stat");
		goto clean;
	}

	if ((fs->bytes = malloc(st.st_size)) == NULL) {
		warn("malloc");
		goto clean;
	}

	if ((f = fopen(path, "r")) == NULL) {
		warn("fopen");
		goto clean;
	}

	p = fs->bytes;
	while ((c = fgetc(f)) != EOF) {
		*(p++) = c;
		fs->sz++;
	}

	if (ferror(f)) {
		warn("fgetc");
		goto clean;
	}

	ret = DGM_OK;
clean:
	fclose(f);

	return (ret);
}

int
dgm_dump_out_file(char *path, struct dgm_file *fs)
{
	FILE			*f = NULL;
	int			 ret = DGM_FAIL;
	size_t			 i;

	DPRINTF(HGD_D_INFO, "Dumping %lu bytes to %s", fs->sz, path);

	if ((f = fopen(path, "w")) == NULL) {
		warn("fopen");
		goto clean;
	}

	for (i = 0; i < fs->sz; i++) {
		if ((fputc((int) fs->bytes[i], f)) == EOF)
			break;
	}

	if (ferror(f)) {
		warn("fgetc");
		goto clean;
	}

	ret = DGM_OK;
clean:
	fclose(f);

	return (ret);
}
