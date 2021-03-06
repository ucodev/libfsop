/**
 * @file path.h
 * @brief File System Operations Library (libfsop)
 *        Path Operations Interface Header
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

#ifndef FSOP_PATH_H
#define FSOP_PATH_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "config.h"

/* Prototypes / Interface */

/**
 * @brief
 *   Checks if 'path' exists.
 *
 * @param path
 *   The path to be checked.
 *
 * @return
 *   If the path exists, 1 is returned. Otherwise, 0 is returned.
 *
 */
#ifdef COMPILE_WIN32
DLLIMPORT
#endif
int fsop_path_exists(const char *path);

/**
 * @brief
 *   Checks if 'path' is a directory.
 *
 * @param path
 *   The path to be checked.
 *
 * @return
 *   If the path is a directory, 1 is returned. Otherwise, 0 is returned.
 *
 */
#ifdef COMPILE_WIN32
DLLIMPORT
#endif
int fsop_path_isdir(const char *path);

/**
 * @brief
 *   Checks if 'path' is a regular file.
 *
 * @param path
 *   The path to be checked.
 *
 * @return
 *   If the path is a regular file, 1 is returned. Otherwise, 0 is returned.
 *
 */
#ifdef COMPILE_WIN32
DLLIMPORT
#endif
int fsop_path_isreg(const char *path);

#ifndef COMPILE_WIN32
/**
 * @brief
 *   Checks if 'path' is a character device.
 *
 * @param path
 *   The path to be checked.
 *
 * @return
 *   If the path is a character device, 1 is returned. Otherwise, 0 is returned.
 *
 */
int fsop_path_ischr(const char *path);

/**
 * @brief
 *   Checks if 'path' is a block device.
 *
 * @param path
 *   The path to be checked.
 *
 * @return
 *   If the path is a block device, 1 is returned. Otherwise, 0 is returned.
 *
 */
int fsop_path_isblk(const char *path);

/**
 * @brief
 *   Checks if 'path' is a named pipe (FIFO).
 *
 * @param path
 *   The path to be checked.
 *
 * @return
 *   If the path is a named pipe (FIFO), 1 is returned. Otherwise, 0 is returned.
 *
 */
int fsop_path_isfifo(const char *path);

/**
 * @brief
 *   Checks if 'path' is a symbolic link.
 *
 * @param path
 *   The path to be checked.
 *
 * @return
 *   If the path is a symbolic link, 1 is returned. Otherwise, 0 is returned.
 *
 */
int fsop_path_islnk(const char *path);

/**
 * @brief
 *   Checks if 'path' is a named socket.
 *
 * @param path
 *   The path to be checked.
 *
 * @return
 *   If the path is a named socket, 1 is returned. Otherwise, 0 is returned.
 *
 */
int fsop_path_issock(const char *path);

/**
 * @brief
 *   Checks if 'path' is readable by others.
 *
 * @param path
 *   The path to be checked.
 *
 * @return
 *   If the path has the +r mode for others, 1 is returned. Otherwise, 0 is returned.
 *   On error, -1 is returned.
 *
 */
int fsop_path_read_other(const char *path);

/**
 * @brief
 *   Checks if 'path' is readable by group.
 *
 * @param path
 *   The path to be checked.
 *
 * @return
 *   If the path has the +r mode for the group, 1 is returned. Otherwise, 0 is returned.
 *   On error, -1 is returned.
 *
 */
int fsop_path_read_group(const char *path);

/**
 * @brief
 *   Checks if 'path' is readable by owner.
 *
 * @param path
 *   The path to be checked.
 *
 * @return
 *   If the path has the +r mode for the owner, 1 is returned. Otherwise, 0 is returned.
 *   On error, -1 is returned.
 *
 */
int fsop_path_read_owner(const char *path);

/**
 * @brief
 *   Checks if 'path' is writable by others.
 *
 * @param path
 *   The path to be checked.
 *
 * @return
 *   If the path has the +w mode for others, 1 is returned. Otherwise, 0 is returned.
 *   On error, -1 is returned.
 *
 */
int fsop_path_write_other(const char *path);

/**
 * @brief
 *   Checks if 'path' is writable by group.
 *
 * @param path
 *   The path to be checked.
 *
 * @return
 *   If the path has the +w mode for the group, 1 is returned. Otherwise, 0 is returned.
 *   On error, -1 is returned.
 *
 */
int fsop_path_write_group(const char *path);

/**
 * @brief
 *   Checks if 'path' is writable by owner.
 *
 * @param path
 *   The path to be checked.
 *
 * @return
 *   If the path has the +w mode for the owner, 1 is returned. Otherwise, 0 is returned.
 *   On error, -1 is returned.
 *
 */
int fsop_path_write_owner(const char *path);

/**
 * @brief
 *   Checks if 'path' is executable by others.
 *
 * @param path
 *   The path to be checked.
 *
 * @return
 *   If the path has the +x mode for others, 1 is returned. Otherwise, 0 is returned.
 *   On error, -1 is returned.
 *
 */
int fsop_path_exec_other(const char *path);

/**
 * @brief
 *   Checks if 'path' is executable by group.
 *
 * @param path
 *   The path to be checked.
 *
 * @return
 *   If the path has the +x mode for the group, 1 is returned. Otherwise, 0 is returned.
 *   On error, -1 is returned.
 *
 */
int fsop_path_exec_group(const char *path);

/**
 * @brief
 *   Checks if 'path' is executable by owner.
 *
 * @param path
 *   The path to be checked.
 *
 * @return
 *   If the path has the +x mode for the owner, 1 is returned. Otherwise, 0 is returned.
 *   On error, -1 is returned.
 *
 */
int fsop_path_exec_owner(const char *path);

/**
 * @brief
 *   Returns the 'path' mode.
 *
 * @param path
 *   The path to be checked.
 *
 * @return
 *   If the path exists, its mode is returned. Otherwise, -1 is returned.
 *
 */
mode_t fsop_path_mode(const char *path);

/**
 * @brief
 *   Returns the 'path' owner id.
 *
 * @param path
 *   The path to be checked.
 *
 * @return
 *   If the path exists, its owner uid is returned. Otherwise, -1 is returned.
 *
 */
uid_t fsop_path_owner(const char *path);

/**
 * @brief
 *   Returns the 'path' group id.
 *
 * @param path
 *   The path to be checked.
 *
 * @return
 *   If the path exists, its group id is returned. Otherwise, -1 is returned.
 *
 */
gid_t fsop_path_group(const char *path);

#endif

#endif

