/**
 * @file file.h
 * @brief File System Operations Library (libfsop)
 *        File Operations Interface Header
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

#ifndef FSOP_FILE_H
#define FSOP_FILE_H

#include <sys/types.h>
#include <sys/stat.h>


/* Prototypes / Interface */

/**
 * @brief
 *   Copies the file referenced by 'src' to destination 'dest'.
 *
 * @param src
 *   The source file.
 *
 * @param dest
 *   The destination file.
 *
 * @param block
 *   The block size that will be used on read/write operations.
 *
 * @return
 *   On success, zero is return. On error, -1 is returned and errno is set
 *   appropriately.
 *
 */
ssize_t fsop_cp(const char *src, const char *dest, size_t block);

/**
 * @brief
 *   Moves the file referenced by 'src' to destination 'dest'.
 *
 * @param src
 *   The source file.
 *
 * @param dest
 *   The destination file.
 *
 * @param block
 *   The block size that will be used on read/write operations.
 *
 * @return
 *   On success, zero is return. On error, -1 is returned and errno is set
 *   appropriately.
 *
 */
ssize_t fsop_mv(const char *from, const char *to, size_t block);

/**
 * @brief
 *   Receives the contents of a file sent by fsop_fsend(). The contents are
 *   written to the file referenced by 'file', which is created with mode bits
 *   'mode'. The file descriptor 'sfd' must be an open file descriptor being
 *   written by fsop_fsend().
 *
 * @param dfd
 *   An open file descriptor.
 *
 * @param file
 *   The file which contents are to be written from 'sfd'.
 *
 * @param block
 *   The block size that will be used on read/write operations.
 *
 * @return
 *   On success, zero is returned. On error, -1 is returned and errno is set
 *   appropriately.
 *
 * @see fsop_fsend()
 *
 */
ssize_t fsop_frecv(int sfd, const char *file, mode_t mode, size_t block);

/**
 * @brief
 *   Sends the contents of the file referenced by 'file' to the file descriptor
 *   'dfd'.
 *
 * @param dfd
 *   An open file descriptor.
 *
 * @param file
 *   The file which contents are to be written to 'dfd'.
 *
 * @param block
 *   The block size that will be used on read/write operations.
 *
 * @return
 *   On success, zero is returned. On error, -1 is returned and errno is set
 *   appropriately.
 *
 */
ssize_t fsop_fsend(int dfd, const char *file, size_t block);

/**
 * @brief
 *   Unlinks the file referenced by 'file'.
 *
 * @param file
 *   The file to be unlinked.
 *
 * @return
 *   On success, zero is returned. On error, -1 is returned and errno is set
 *   appropriately.
 *
 */
int fsop_unlink(const char *file);

#endif

