/**
 * @file config.h
 * @brief File System Operations Library (libfsop)
 *        Configuration Header
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

#ifndef FSOP_CONFIG_H
#define FSOP_CONFIG_H

#ifdef COMPILE_WIN32
 #include <windows.h>

 #if BUILDING_DLL
  #define DLLIMPORT __declspec (dllexport)
 #else /* Not BUILDING_DLL */
  #define DLLIMPORT __declspec (dllimport)
 #endif /* Not BUILDING_DLL */
 
 #define strtok_r           strtok_s
 #define unlink             _unlink
 #define stat               _stat
 #define mkdir              _mkdir
 
 #define CONFIG_PATH_MAX    260
#endif


#endif

