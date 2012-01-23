#ifndef ROM_H_
#define ROM_H_

/* ROM Offsets */
#define GNS_OFS_CONSOLE		0x100
#define GNS_OFS_COPYRIGHT	0x110
#define GNS_OFS_NAME_DOMESTIC	0x120
#define GNS_OFS_NAME_OVERSEAS	0x150
#define GNS_OFS_TYPE		0x180
#define GNS_OFS_PRODUCT_CODE	0x182
#define GNS_OFS_CHECKSUM	0x18e
#define GNS_OFS_IO_SUPPORT	0x190
#define GNS_OFS_CAPACITY	0x1a0
#define GNS_OFS_RAM		0x1a8
#define GNS_OFS_MODEM_DATA	0x1bc
#define GNS_OFS_MEMO		0x1c8
#define GNS_OFS_COUNTRY		0x1f0

/* padding before first field */
#define GNS_OFS_FIELD_PAD	GNS_OFS_CONSOLE

/* ROM Field Lengths */
#define GNS_FLEN_CONSOLE	(GNS_OFS_COPYRIGHT - GNS_OFS_CONSOLE)
#define GNS_FLEN_COPYRIGHT	(GNS_OFS_NAME_DOMESTIC - GNS_OFS_COPYRIGHT)
#define GNS_FLEN_NAME_DOMESTIC	(GNS_OFS_NAME_OVERSEAS - GNS_OFS_NAME_DOMESTIC)
#define GNS_FLEN_NAME_OVERSEAS	(GNS_OFS_TYPE - GNS_OFS_NAME_OVERSEAS)
#define GNS_FLEN_TYPE		(GNS_OFS_PRODUCT_CODE - GNS_OFS_TYPE)
#define GNS_FLEN_PRODUCT_CODE	(GNS_OFS_CHECKSUM - GNS_OFS_PRODUCT_CODE)
#define GNS_FLEN_CHECKSUM	(GNS_OFS_IO_SUPPORT - GNS_OFS_CHECKSUM)
#define GNS_FLEN_IO_SUPPORT	(GNS_OFS_CAPACITY - GNS_OFS_IO_SUPPORT)
#define GNS_FLEN_CAPACITY	(GNS_OFS_RAM - GNS_OFS_CAPACITY)
#define GNS_FLEN_RAM		(GNS_OFS_MODEM_DATA - GNS_OFS_RAM)
#define GNS_FLEN_MODEM_DATA	(GNS_OFS_MEMO - GNS_OFS_MODEM_DATA)
#define GNS_FLEN_MEMO		(GNS_OFS_COUNTRY - GNS_OFS_MEMO)
#define GNS_FLEN_COUNTRY	(1)

struct gns_rom_header {
	/* pad, as first field is at 0x100 */
	char		pad[GNS_OFS_FIELD_PAD];
	/* Actual fields start here */
	char		console_name[GNS_FLEN_CONSOLE];
	char		copyright[GNS_FLEN_COPYRIGHT];
	char		name_domestic[GNS_FLEN_NAME_DOMESTIC];
	char		name_overseas[GNS_FLEN_NAME_OVERSEAS];
	char		type[GNS_FLEN_TYPE];
	char		product_code[GNS_FLEN_PRODUCT_CODE];
	char		checksum[GNS_FLEN_CHECKSUM];
	char		io_support[GNS_FLEN_IO_SUPPORT];
	char		capacity[GNS_FLEN_CAPACITY];
	char		ram[GNS_FLEN_RAM];
	char		modem_data[GNS_FLEN_MODEM_DATA];
	char		memo[GNS_FLEN_MEMO];
	char		country[GNS_FLEN_COUNTRY];
};

struct gns_rom_header_mapping {
	int		 offset;
	int		 length;
	char		 *name;
	void		(*printer)(char *, void *, size_t);
};

/* protos */
int		gns_load_rom_header(struct gns_rom_header *, char *);
void		gns_print_rom_header(struct gns_rom_header *hdr);
void		gns_print_rom_header_field_hex(char *title, void *data, size_t ct);
void		gns_print_rom_header_field_char(char *title, void *data, size_t ct);

#endif
