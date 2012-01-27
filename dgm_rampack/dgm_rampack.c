#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/dgm_common.h"

int		dgm_unpack(char *, char *);
int		dgm_pack(char *, char *);
void		usage();

int
main(int argc, char **argv)
{
	int			ch;
	int			(*handler)(char *, char *) = NULL;

	while ((ch = getopt(argc, argv, "pu")) != -1) {
		switch (ch) {
		case 'p':
			handler = dgm_pack;
			break;
		case 'u':
			handler = dgm_unpack;
			break;
		default:
			usage();
			/* NOREACH */
			break;
		}
	}
	argc -= optind;
	argv += optind;

	if (handler == NULL)
		usage();

	handler(argv[0], argv[1]);

	exit(EXIT_SUCCESS);
}

void
usage()
{
	fprintf(stderr, "Packing usage:\t\tdgm_rampack -p <infile> <outfile>\n");
	fprintf(stderr, "Unpacking usage:\tdgm_rampack -u <infile> <outfile>\n");
	exit(EXIT_FAILURE);
}

int
dgm_unpack(char *inpath, char *outpath)
{
	FILE			*in = NULL, *out = NULL;
	int			 c, ret = DGM_FAIL;

	if ((in = fopen(inpath, "r")) == NULL) {
		warn("fopen in");
		goto clean;
	}

	if ((out = fopen(outpath, "w")) == NULL) {
		warn("fopen out");
		goto clean;
	}

	while ((c = fgetc(in)) != EOF) {
		if (fputc(c, out) == EOF) {
			warn("fputc");
			goto clean;
		}

		/* skip the next byte */
		if ((c = fgetc(in)) == EOF)
			break;
	}

	if (ferror(in)) {
		warn("fgetc");
		goto clean;
	}

	ret = DGM_OK;
clean:
	if (in)
		fclose(in);
	if (out)
		fclose(out);

	return (ret);
}


int
dgm_pack(char *inpath, char *outpath) {
	FILE			*in = NULL, *out = NULL;
	int			 c, ret = DGM_FAIL;

	printf("Packing %s -> %s\n", inpath, outpath);

	if ((in = fopen(inpath, "r")) == NULL) {
		warn("fopen in");
		goto clean;
	}

	if ((out = fopen(outpath, "w")) == NULL) {
		warn("fopen out");
		goto clean;
	}

	while ((c = fgetc(in)) != EOF) {
		if (fputc(c, out) == EOF) {
			warn("fputc");
			goto clean;
		}

		/* skip the next byte */
		if ((c = fputc(0xd0, out)) == EOF) {
			warn("fputc");
			goto clean;
		}
	}

	if (ferror(in)) {
		warn("fgetc");
		goto clean;
	}

	ret = DGM_OK;
clean:
	if (in)
		fclose(in);
	if (out)
		fclose(out);

	return (ret);
}
