/**
 * @file dir.h
 * @brief File System Operations Library (libfsop)
 *        Directory Operations Interface Header
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

#ifndef FSOP_DIR_H
#define FSOP_DIR_H

#include <sys/types.h>
#include <sys/stat.h>

#include "config.h"

/* Directory Walk Order */
enum {
	FSOP_WALK_PREORDER = 1,
	FSOP_WALK_INORDER,
	FSOP_WALK_POSTORDER
};


/* Prototypes / Interface */

/**
 * @brief
 *   Creates the directory described by 'path', making parent directories as
 *   needed.
 *
 * @param path
 *   New directory path
 *
 * @param mode
 *   Directory mode bits.
 *
 * @return
 *   On success, zero is returned. On error, -1 is returned and errno is set
 *   appropriately.
 *
 */
#ifdef COMPILE_WIN32
DLLIMPORT
#endif
int fsop_pmkdir(const char *path, mode_t mode);

/**
 * @brief
 *   Performs a traversal of the directory pointed by 'dir'. This functions is
 *   recursive, so each time a subdirectory is found, fsop_walkdir() is called
 *   with that subdirectory as it's 'dir' parameter. The 'prefix' parameter
 *   will be used as prefix for the 'rpath' parameter of 'action'. 'action' is
 *   a user defined function which will be called for each element found in
 *   the directory 'dir' ('.' and '..' are ignored). When entering a directory,
 *   the 'action' user function will have the 'order' parameter set to
 *   FSOP_WALK_PREORDER. When walking through the same directory level, 'order'
 *   will have the value FSOP_WALK_INORDER. When leaving the current directory,
 *   'order' will have the value FSOP_WALK_POSTORDER. 'fpath' is the full path
 *   for the found element inside the current directory. 'arg' is an optional
 *   argument that is passed to 'action'.
 *
 * @param dir
 *   The target directory.
 *
 * @param prefix
 *   The prefix value for 'rpath'.
 *
 * @param action
 *   User defined function called for each element found inside 'dir'.
 *   (see description above).
 *
 * @param arg
 *   Optional argument, passed to 'action'.
 *
 * @return
 *   On success, zero is returned. On error, -1 is returned and errno is set
 *   appropriately.
 *
 */
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
		void *arg);

/**
 * @brief
 *   Copy the directory and all its contents from path 'src' to path 'dst'.
 *
 * @param src
 *   The source directory path.
 *
 * @param dest
 *   The destination directory path.
 *
 * @param block
 *   The block size to be used for file copy.
 *
 * @return
 *   On success, zero is returned. On error, -1 is returned and errno is set
 *   appropriately.
 *
 */
#ifdef COMPILE_WIN32
DLLIMPORT
#endif
int fsop_cpdir(const char *src, const char *dest, size_t block);

/**
 * @brief
 *   Move the directory and all its contents from path 'src' to path 'dst'.
 *
 * @param src
 *   The source directory path.
 *
 * @param dest
 *   The destination directory path. The destination directory must not exist.
 *   If it does, it must be an empty directory.
 *
 * @param block
 *   The block size to be used for file copy.
 *
 * @return
 *   On success, zero is returned. On error, -1 is returned and errno is set
 *   appropriately.
 *
 */
#ifdef COMPILE_WIN32
DLLIMPORT
#endif
int fsop_mvdir(const char *src, const char *dest, size_t block);

/**
 * @brief
 *   Deletes the directory 'dir' and all its contents.
 *
 * @param dir
 *   The directory path to be deleted.
 *
 * @return
 *   On success, zero is returned. On error, -1 is returned and errno is set
 *   appropriately.
 * 
 */
#ifdef COMPILE_WIN32
DLLIMPORT
#endif
int fsop_rmdir(const char *dir);

#endif

