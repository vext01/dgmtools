#include <sys/types.h>

#include <err.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "dgm_common.h"
#include "dgm_romlib.h"

HGD_DEBUG_INIT

/* A blank sonic3 RAM image */

#define S3_RAM_SZ		512
unsigned char			s3_ram[S3_RAM_SZ] = {
	0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0x80, 0x00, 0x00,
	0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01,
	0x02, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80,
	0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x80, 0x00, 0x00, 0x00,
	0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02,
	0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00,
	0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80,
	0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00,
	0x4c, 0x44, 0x2e, 0x5a, 0xd0, 0xd0, 0x80, 0x00, 0x00, 0x00, 0x80,
	0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00,
	0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x02, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00,
	0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x80,
	0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x02, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00,
	0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x4c, 0x44,
	0x2e, 0x5a, 0xd0, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x44, 0xed,
	0x3e, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0,
	0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x42, 0x44, 0xed, 0x3e, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0,
	0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0,
	0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0,
	0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0,
	0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0,
	0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0,
	0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0,
	0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0,
	0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0,
	0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0,
	0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0,
	0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0,
	0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0,
	0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0,
	0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0,
	0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0,
	0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0,
	0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0,
	0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0,
	0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0
};

#define	S3_SAVE_SLOTS_START		0xb4
#define	S3_SAVE_SLOT_LEN		0x8
#define S3_CHECKSUM_OFFSET		0xe6
#define S3_CHECKSUM_START		S3_SAVE_SLOTS_START
#define S3_CHECKSUM_END			S3_CHECKSUM_OFFSET - 2

#define S3_ALL_SAVES_LEN		0x3e
#define S3_SECOND_COPY_OFFSET		0xfa

/* fields within a save slot */
#define S3_SAVE_OFFSET_USED			0x00
#define S3_SAVE_OFFSET_CHARACTER		0x02
#define S3_SAVE_OFFSET_ZONE			0x03
#define S3_SAVE_OFFSET_SPECIAL_STAGE_COUNT	0x04
#define S3_SAVE_OFFSET_EM_COUNT			0x05
#define S3_SAVE_OFFSET_EMS_COLLECTED		0x06 /* bitfield */
#define S3_SAVE_OFFSET_SPECIAL_STAGES_ENTERED	0x07 /* bitfield */

int
s3_write_second_copy(unsigned char *ram)
{
	memcpy(ram + S3_SECOND_COPY_OFFSET, ram + S3_SAVE_SLOTS_START, S3_ALL_SAVES_LEN);
	return (DGM_OK);
}

int
s3_gen_cksum(unsigned char *ram, unsigned char ret_cksum[2])
{
	int			 ret = DGM_OK;
	unsigned char		*p;
	uint16_t		 word = 0;
	int			 cc;
	uint16_t		 cksum;

	cksum = 0;
	p = ram + S3_CHECKSUM_START;
	while(p <= ram + S3_CHECKSUM_END) {

		word = 0;

		/* read bytes */
		word |= *(p++) << 8;
		word |= *(p++);

		/* transform cksum */
		cksum ^= word;
		cc = cksum & 0x1; /* emulate condition code ;) */
		cksum >>= 1;

		if (cc)
			cksum ^= 0x8810;
	}

	ret_cksum[0] = (unsigned char) (cksum >> 8);
	ret_cksum[1] = (unsigned char) (cksum & 0x00ff);

	return (ret);
}

/*
 * calculates a ram checksum for a given save slot
 */
int
s3_write_checksum(unsigned char *ram)
{
	unsigned char		sum[2];

	/* these must be 66/68 */
	ram[S3_CHECKSUM_OFFSET - 2] = (unsigned char) 66;
	ram[S3_CHECKSUM_OFFSET - 1] = (unsigned char) 68;

	s3_gen_cksum(ram, sum);

	/* write back checksum */
	ram[S3_CHECKSUM_OFFSET] = sum[0];
	ram[S3_CHECKSUM_OFFSET+1] = sum[1];

	return (DGM_OK);
}

int
s3_test(char *outpath)
{
	struct dgm_file		fs;
	int			ret = DGM_FAIL;

	memset(&fs, 0, sizeof(struct dgm_file));
	if ((fs.bytes = calloc(1, S3_RAM_SZ)) == NULL) {
		warn("malloc");
		goto clean;
	}
	memcpy(fs.bytes, s3_ram, S3_RAM_SZ);
	fs.sz = S3_RAM_SZ;

	fs.bytes[S3_SAVE_SLOTS_START + S3_SAVE_OFFSET_ZONE] = (unsigned char) 7;
	fs.bytes[S3_SAVE_SLOTS_START + S3_SAVE_OFFSET_EMS_COLLECTED] = (unsigned char) 0xff;
	fs.bytes[S3_SAVE_SLOTS_START + S3_SAVE_OFFSET_EM_COUNT] = (unsigned char) 7;
	//fs.bytes[S3_SAVE_SLOTS_START + S3_SAVE_OFFSET_USED] = (unsigned char) 128;

	s3_write_checksum(fs.bytes);
	s3_write_second_copy(fs.bytes);

	dgm_dump_out_file(outpath, &fs);

	ret = DGM_OK;
clean:

	return (ret);
}

void
usage()
{
	printf("XXX\n");
	exit(EXIT_FAILURE);
}

#define SLOT_CHECK							\
	if ((slot < 0) || (slot > 6)) {					\
		DPRINTF(HGD_D_ERROR, "Slot out of range: %d", slot);	\
		return (DGM_FAIL);					\
	}

int
s3_set_character(unsigned char *ram, int slot, unsigned char val)
{
	DPRINTF(HGD_D_INFO, "set");
	SLOT_CHECK;
	ram[S3_SAVE_SLOTS_START + ((slot - 1) * S3_SAVE_SLOT_LEN) + S3_SAVE_OFFSET_CHARACTER] = val;

	return (DGM_OK);
}

int
s3_set_zone(unsigned char *ram, int slot, unsigned char val)
{
	DPRINTF(HGD_D_INFO, "set");
	SLOT_CHECK;
	ram[S3_SAVE_SLOTS_START + ((slot - 1) * S3_SAVE_SLOT_LEN) + S3_SAVE_OFFSET_ZONE] = val;

	return (DGM_OK);
}

int
s3_set_emeralds(unsigned char *ram, int slot, unsigned char val)
{
	int				i = 0;
	uint8_t				ems = 0;


	DPRINTF(HGD_D_INFO, "set");
	SLOT_CHECK;

	ram[S3_SAVE_SLOTS_START + ((slot - 1) * S3_SAVE_SLOT_LEN) + S3_SAVE_OFFSET_EMS_COLLECTED] = val;

	/* count the number of emeralds passed in bitfield */
	for (i = 0; i < 8; i++)
		ems += ((val >> i) & 0x1);

	ram[S3_SAVE_SLOTS_START + ((slot - 1) * S3_SAVE_SLOT_LEN) + S3_SAVE_OFFSET_EM_COUNT] = ems;

	return (DGM_OK);
}

int
s3_set_used(unsigned char *ram, int slot)
{
	DPRINTF(HGD_D_INFO, "set");
	SLOT_CHECK;
	ram[S3_SAVE_SLOTS_START + ((slot - 1) * S3_SAVE_SLOT_LEN) + S3_SAVE_OFFSET_USED] = 0;

	return (DGM_OK);
}

int
s3_set_megaram(unsigned char *ram, int slot)
{
	int		i;
	int		character = 0;

	DPRINTF(HGD_D_INFO, "Making megaram");

	for (i = 0; i < 7; i++, character++) {
		s3_set_character(ram, i, character % 3);
		s3_set_zone(ram, i, 7);
		s3_set_emeralds(ram, i, 0xfe);
		s3_set_used(ram, i);
	}

	return (DGM_OK);
}

#define S3_NUM_SAVES		6
int
main(int argc, char **argv)
{
	int			ch, slot = -1;
	struct dgm_file		fs, pad_fs, *write_fs;
	int			ret = DGM_FAIL, err, pad = 0, megaram = 0;

	memset(&fs, 0, sizeof(struct dgm_file));
	if ((fs.bytes = calloc(1, S3_RAM_SZ)) == NULL) {
		warn("malloc");
		goto clean;
	}
	memcpy(fs.bytes, s3_ram, S3_RAM_SZ);
	fs.sz = S3_RAM_SZ;

	while ((ch = getopt(argc, argv, "c:e:hMps:x:z:")) != -1) {
		err = DGM_OK;

		switch (ch) {
		case 'c': /* character */
			err = s3_set_character(fs.bytes, slot, strtoll(optarg, 0, 0));
			break;
		case 'e': /* emeralds collected bitfield */
			err = s3_set_emeralds(fs.bytes, slot, strtoll(optarg, 0, 0));
			break;
		case 'M':
			err = s3_set_megaram(fs.bytes, slot);
			megaram = 1;
			break;
		case 'p':
			pad = 1;
			break;
		case 's': /* slot */
			slot = atoi(optarg);
			err = s3_set_used(fs.bytes, slot);
			break;
		case 'x': /* debug */
			hgd_debug = atoi(optarg);
			break;
		case 'z': /* zone */
			err = s3_set_zone(fs.bytes, slot, strtoll(optarg, 0, 0));
			break;
		case 'h':
		default:
			usage();
			/* NOREACH */
			break;
		}

		if (err == DGM_FAIL)
			goto clean;
	}
	argc -= optind;
	argv += optind;

	if ((megaram == 0 ) && (slot == -1)) {
		DPRINTF(HGD_D_ERROR, "Please select a slot");
		goto clean;
	}

	if (argc != 1) {
		DPRINTF(HGD_D_ERROR, "Please provide an outfile");
		goto clean;
	}

	/* OK, let's checksum this and copy the backup */
	s3_write_checksum(fs.bytes);
	s3_write_second_copy(fs.bytes);

	/* if we need to use dgen (emulator), we word align (pad) */
	write_fs = &fs;
	if (pad) {
		DPRINTF(HGD_D_INFO, "Padding ram");
		if (dgm_dgen_ram_pad(&fs, &pad_fs) != DGM_OK) {
			DPRINTF(HGD_D_ERROR, "padding failed");
			goto clean;
		}

		write_fs = &pad_fs;
	}

	/* and write away */
	dgm_dump_out_file(argv[0], write_fs);

	ret = DGM_OK;
clean:
	return (ret);
}
