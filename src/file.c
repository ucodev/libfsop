/**
 * @file file.c
 * @brief File System Operations Library (libfsop)
 *        File Operations Interface
 *
 * Date: 14-01-2015
 * 
 * Copyright 2012-2015 Pedro A. Hortas (pah@ucodev.org)
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
#include <stdlib.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "config.h"
#include "mm.h"
#include "path.h"
#include "file.h"


static void _fsop_close_safe(int fd) {
	while (close(fd) < 0) {
		if (errno != EINTR)
			break;
	}
}

static ssize_t _fsop_fxchg(int sfd, int dfd, size_t block) {
	int errsv = 0, ret = 0;
	ssize_t count = 0;
	char *buf = NULL;

	if (!(buf = mm_alloc(block))) {
		errsv = errno;
		goto _error2;
	}

	while ((ret = read(sfd, buf, block)) == block) {
		if (write(dfd, buf, block) != block)
			goto _error;

		count += block;
	}

	if (ret >= 0) {
		if (write(dfd, buf, ret) != ret)
			goto _error;

		count += ret;
	} else {
		goto _error;
	}

	mm_free(buf);

	return count;

_error:
	errsv = errno;
	mm_free(buf);
_error2:
	errno = errsv;
	return -1;
}

ssize_t fsop_frecv(int sfd, const char *file, mode_t mode, size_t block) {
	int dfd = 0;
	ssize_t count = 0;

	fsop_unlink(file);

	if ((dfd = open(file, O_WRONLY | O_CREAT, mode)) < 0)
		return -1;

	if ((count = _fsop_fxchg(sfd, dfd, block)) < 0)
		return -1;

	_fsop_close_safe(dfd);

	return count;
}

ssize_t fsop_fsend(int dfd, const char *file, size_t block) {
	int sfd = 0;
	ssize_t count = 0;

	if ((sfd = open(file, O_RDONLY)) < 0)
		return -1;

	if ((count = _fsop_fxchg(sfd, dfd, block)) < 0)
		return -1;

	_fsop_close_safe(sfd);

	return count;
}

ssize_t fsop_cp(const char *src, const char *dest, size_t block) {
	int dfd = 0;
	ssize_t count = 0;
	struct stat st;

	if (stat(src, &st) < 0)
		return -1;

	fsop_unlink(dest);

	if ((dfd = open(dest, O_WRONLY | O_CREAT, st.st_mode)) < 0)
		return -1;

	count = fsop_fsend(dfd, src, block);

	_fsop_close_safe(dfd);

	return count;
}

ssize_t fsop_mv(const char *from, const char *to, size_t block) {
	ssize_t count = 0;
	struct stat st;

	if (!rename(from, to)) {
		if (stat(to, &st) < 0)
			return -1;

		return st.st_size;
	}

	if ((count = fsop_cp(from, to, block)) < 0)
		return -1;

	if (fsop_unlink(from) < 0)
		return -1;

	return count;
}

int fsop_unlink(const char *file) {
	return unlink(file);
}

