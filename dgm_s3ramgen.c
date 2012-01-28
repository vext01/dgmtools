#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int
main(int argc, char **argv)
{
	FILE			*infile = NULL;
	uint16_t		 offset, len, res = 0, word = 0;
	char			*filename;
	int			 ch, cc;

	if (argc != 4) {
		printf("XXX: filename offset length\n");
		exit (EXIT_FAILURE);
	}

	filename = argv[1];
	offset = strtoll(argv[2], NULL,  0);
	len = strtoll(argv[3], NULL, 0);

	printf("Checksum %u bytes starting at 0x%02x from %s\n",
	    len, offset, filename);

	if ((infile = fopen(filename, "r")) == NULL)
		errx(EXIT_FAILURE, "fopen");

	if (fseek(infile, offset, SEEK_SET) < 0 )
		errx(EXIT_FAILURE, "fseek");

	for (; len > 0; len--) {

		word = 0;

		/* read byte 1 */
		if ((ch = fgetc(infile)) == EOF) {
			errx(EXIT_FAILURE, "fgetc");
		}
		word |= ch << 8;
		printf("byte1: %02x\n", ch);

		/* read byte 2 */
		if ((ch = fgetc(infile)) == EOF) {
			errx(EXIT_FAILURE, "fgetc");
		}
		word |= ch;
		printf("byte2: %02x\n", ch);

		printf("bytes: %04x\n", word);

		res ^= word;

		printf("xor: 0x%04x\n", res);

		cc = res & 0x1; /* emulate condition code ;) */

		printf("cc: 0x%04x\n", cc);

		//res = (cc << 15) | (res >> 1);
		//res  = (res >> 1) & (cc << 15);
		res >>= 1;

		printf("barrel: 0x%04x\n", res);

		if (cc) {
			res ^= 0x8810;
			printf("^ 8810: 0x%04x\n", res);
		}


		printf("end loop %d: 0x%04x\n\n", len, res);

	}

	printf("0x%04x %u\n", res, res);

	fclose(infile);

}
