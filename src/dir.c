/**
 * @file dir.c
 * @brief File System Operations Library (libfsop)
 *        Directory Operations Interface
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
#include <dirent.h>
#include <stddef.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "config.h"
#include "mm.h"
#include "path.h"
#include "dir.h"
#include "file.h"

#ifdef COMPILE_WIN32
/* 
 * WARNING and TODO:
 *
 *  - This is a fast hack to implement a readdir_r() on windows (MinGW).
 *  - This is NOT totally safe, as calls to readdir() outside of libfsop
 *    will interfere with this implementation.
 *  - A new version of this function based on FindNextFile() must be
 *    implemented.
 *
 */

static HANDLE _mutex_readdir;
static int _mutex_readdir_initialized = 0;

static int readdir_r(DIR *dirp, struct dirent *entry, struct dirent **result) {
	if (!_mutex_readdir_initialized) {
		_mutex_readdir = CreateMutex(NULL, FALSE, NULL);
		_mutex_readdir_initialized = 1;
	}
	
	WaitForSingleObject(_mutex_readdir, INFINITE);
	
	if (!(*result = readdir(dirp))) {
		ReleaseMutex(_mutex_readdir);
		return -1;
	}
	
	ReleaseMutex(_mutex_readdir);
	
	memcpy(entry, *result, sizeof(struct dirent));
	
	return 0;
}
#endif

#ifdef COMPILE_WIN32
DLLIMPORT
#endif
int fsop_pmkdir(const char *path, mode_t mode) {
	char *lpath = NULL, *cpath = NULL, *ptr = NULL, *saveptr = NULL;
	size_t len = 0;
	int errsv = 0;

	if (!(lpath = mm_alloc(strlen(path) + 1)))
		return -1;

	strcpy(lpath, path);

	if (!(ptr = strtok_r(lpath, "/", &saveptr))) {
		int ret = 0;

		if (!fsop_path_exists(lpath)) {
#ifdef COMPILE_WIN32
			ret = mkdir(lpath);
#else
			ret = mkdir(lpath, mode);
#endif
			errsv = errno;
		}

		mm_free(lpath);
		errno = errsv;

		return ret;
	}

	len = strlen(ptr) + 1 + (path[0] == '/');

	if (!(cpath = mm_alloc(len))) {
		errsv = errno;
		mm_free(lpath);
		errno = errsv;
		return -1;
	}

	memset(cpath, 0, len);
	cpath[0] = path[0] == '/' ? '/' : 0;
	strcat(cpath, ptr);

	if (!fsop_path_exists(cpath)) {
#ifdef COMPILE_WIN32
		if (mkdir(cpath) < 0)
#else
		if (mkdir(cpath, mode) < 0)
#endif
			goto _error;
	}

	while ((ptr = strtok_r(NULL, "/", &saveptr))) {
		len += strlen(ptr) + 2;

		if (!(cpath = mm_realloc(cpath, len)))
			goto _error;

		strcat(cpath, "/");
		strcat(cpath, ptr);

		if (!fsop_path_exists(cpath)) {
#ifdef COMPILE_WIN32
			if (mkdir(cpath) < 0)
#else
			if (mkdir(cpath, mode) < 0)
#endif
				goto _error;
		}
	}

	mm_free(lpath);
	mm_free(cpath);

	return 0;
_error:
	errsv = errno;
	mm_free(cpath);
	mm_free(lpath);
	errno = errsv;
	return -1;
}

#ifdef COMPILE_WIN32
DLLIMPORT
#endif
int fsop_walkdir(
		const char *dir,
		const char *prefix,
		int (*action)
			(int order,
			const char *fpath,
			const char *rpath,
			void *arg),
		void *arg)
{
	DIR *sdp = NULL;
	struct dirent *entryp = NULL, *result = NULL;
	char *fpath = NULL, *rpath = NULL;
	int errsv = 0;

	if (!fsop_path_isdir(dir))
		return -1;

	if (!(sdp = opendir(dir)))
		return -1;

#ifdef COMPILE_WIN32
	if (!(entryp = mm_alloc(offsetof(struct dirent, d_name) + CONFIG_PATH_MAX + 1)))
#else
	if (!(entryp = mm_alloc(offsetof(struct dirent, d_name) + pathconf(dir, _PC_NAME_MAX) + 1)))
#endif
		return -1;

	if (action(FSOP_WALK_PREORDER, dir, prefix, arg) < 0)
		goto _error3;

	while (!(errsv = readdir_r(sdp, entryp, &result))) {
		if (!result)
			break;

		if (!strcmp(result->d_name, ".") || !strcmp(result->d_name, ".."))
			continue;

		if (!(fpath = mm_alloc(strlen(dir) + strlen(result->d_name) + 2))) {
			errsv = errno;
			goto _error3;
		}

		if (!(rpath = mm_alloc((prefix ? strlen(prefix) : 0) + strlen(result->d_name) + 2))) {
			errsv = errno;
			goto _error2;
		}

		sprintf(fpath, "%s/%s", dir, result->d_name);

		if (prefix)
			sprintf(rpath, "%s/%s", prefix, result->d_name);
		else
			sprintf(rpath, "%s", result->d_name);

		if (action(FSOP_WALK_INORDER, fpath, rpath, arg) < 0)
			goto _error;

		mm_free(fpath);
		mm_free(rpath);
	}

	if (action(FSOP_WALK_POSTORDER, dir, prefix, arg) < 0)
		goto _error3;

	mm_free(entryp);
	closedir(sdp);

	return -!!(errno = errsv);
_error:
	errsv = errno;
	mm_free(rpath);
_error2:
	mm_free(fpath);
_error3:
	mm_free(entryp);
	closedir(sdp);
	errno = errsv;
	return -1;
}

static int _cpdir_action(
		int order,
		const char *fpath,
		const char *rpath,
		void *arg)
{
	struct stat st;

	if (order == FSOP_WALK_PREORDER) {
		if (stat(fpath, &st) < 0)
			return -1;

		return fsop_pmkdir(rpath, st.st_mode);
	} else if (order == FSOP_WALK_INORDER) {
		if (stat(fpath, &st) < 0)
			return -1;

		if (S_ISDIR(st.st_mode)) {
			if (fsop_cpdir(fpath, rpath, *(size_t *) arg) < 0)
				return -1;
		} else {
			return fsop_cp(fpath, rpath, *(size_t *) arg);
		}
	}

	return 0;
}

#ifdef COMPILE_WIN32
DLLIMPORT
#endif
int fsop_cpdir(const char *src, const char *dest, size_t block) {
	return fsop_walkdir(src, dest, &_cpdir_action, &block);
}		

static int _rmdir_action(
		int order,
		const char *fpath,
		const char *rpath,
		void *arg)
{
	struct stat st;

	if (order == FSOP_WALK_POSTORDER) {
		if (stat(fpath, &st) < 0)
			return -1;

		return rmdir(fpath);
	} else if (order == FSOP_WALK_INORDER) {
		if (stat(fpath, &st) < 0)
			return -1;

		if (S_ISDIR(st.st_mode)) {
			if (fsop_rmdir(fpath) < 0)
				return -1;
		} else {
			return unlink(fpath);
		}
	}

	return 0;
}

#ifdef COMPILE_WIN32
DLLIMPORT
#endif
int fsop_rmdir(const char *dir) {
	return fsop_walkdir(dir, NULL, &_rmdir_action, NULL);
}		

#ifdef COMPILE_WIN32
DLLIMPORT
#endif
int fsop_mvdir(const char *src, const char *dest, size_t block) {
	if (!rename(src, dest))
		return 0;

	if (fsop_path_exists(dest)) {
		/* Must be an empty directory */
		if (rmdir(dest) < 0)
			return -1;
	}

	if (fsop_cpdir(src, dest, block) < 0)
		return -1;

	if (fsop_rmdir(src) < 0)
		return -1;

	return 0;
}

