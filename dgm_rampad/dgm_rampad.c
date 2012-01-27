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

#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/dgm_common.h"

int		dgm_unpad(char *, char *);
int		dgm_pad(char *, char *);
void		usage();

int
main(int argc, char **argv)
{
	int			ch;
	int			(*handler)(char *, char *) = NULL;

	while ((ch = getopt(argc, argv, "pu")) != -1) {
		switch (ch) {
		case 'p':
			handler = dgm_pad;
			break;
		case 'u':
			handler = dgm_unpad;
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
	fprintf(stderr, "Pading usage:\t\tdgm_rampad -p <infile> <outfile>\n");
	fprintf(stderr, "Unpading usage:\tdgm_rampad -u <infile> <outfile>\n");
	exit(EXIT_FAILURE);
}

int
dgm_unpad(char *inpath, char *outpath)
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
dgm_pad(char *inpath, char *outpath) {
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
