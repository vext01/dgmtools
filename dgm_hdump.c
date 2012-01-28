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
#include <stdlib.h>

#include "dgm_romlib.h"
#include "dgm_common.h"

int
main(int argc, char **argv)
{
	struct dgm_rom_header		hdr;

	if (argc != 2) {
		fprintf(stderr, "usage XXX\n");
		exit(EXIT_FAILURE);
	}

	if (dgm_load_rom_header(&hdr, argv[1]) != DGM_OK) {
		fprintf(stderr, "load header failed XXX\n");
		exit(EXIT_FAILURE);
	}

	dgm_print_rom_header(&hdr);

	exit(EXIT_SUCCESS);
}
