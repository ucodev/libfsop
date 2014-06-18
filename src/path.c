/**
 * @file path.c
 * @brief File System Operations Library (libfsop)
 *        Path Operations Interface
 *
 * Date: 18-06-2014
 * 
 * Copyright 2012-2014 Pedro A. Hortas (pah@ucodev.org)
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

#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>

#include "path.h"


int fsop_path_exists(const char *path) {
	return !stat(path, (struct stat [1]) { });
}

int fsop_path_isdir(const char *path) {
	struct stat st;

	if (stat(path, &st) < 0)
		return -1;

	return S_ISDIR(st.st_mode);
}

int fsop_path_isreg(const char *path) {
	struct stat st;

	if (stat(path, &st) < 0)
		return -1;

	return S_ISREG(st.st_mode);
}

int fsop_path_ischr(const char *path) {
	struct stat st;

	if (stat(path, &st) < 0)
		return -1;

	return S_ISCHR(st.st_mode);
}

int fsop_path_isblk(const char *path) {
	struct stat st;

	if (stat(path, &st) < 0)
		return -1;

	return S_ISBLK(st.st_mode);
}

int fsop_path_isfifo(const char *path) {
	struct stat st;

	if (stat(path, &st) < 0)
		return -1;

	return S_ISFIFO(st.st_mode);
}

int fsop_path_islnk(const char *path) {
	struct stat st;

	if (stat(path, &st) < 0)
		return -1;

	return S_ISLNK(st.st_mode);
}

int fsop_path_issock(const char *path) {
	struct stat st;

	if (stat(path, &st) < 0)
		return -1;

	return S_ISSOCK(st.st_mode);
}

