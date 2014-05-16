/**
 * @file mv.c
 * @brief File System Operations Library (libfsop)
 *        Move File Example
 *
 * Date: 03-11-2012
 * 
 * Copyright 2012 Pedro A. Hortas (pah@ucodev.org)
 *
 * This file is part of libfsop.
 *
 * libfsop is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libfsop is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libfsop.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <fsop/file.h>

#define BLOCK_SIZE	8192

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <src file> <dest file>\n", argv[0]);
		return 1;
	}

	if (fsop_mv(argv[1], argv[2], BLOCK_SIZE) < 0) {
		fprintf(stderr, "fsop_cp() error: %s\n", strerror(errno));
		return 1;
	}

	return 0;
}

