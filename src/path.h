/**
 * @file path.h
 * @brief File System Operations Library (libfsop)
 *        Path Operations Interface Header
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

#ifndef FSOP_PATH_H
#define FSOP_PATH_H

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
int fsop_path_isreg(const char *path);

#endif

