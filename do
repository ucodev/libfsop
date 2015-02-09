#!/bin/bash

## Detect compiler ##
. ./lib/sh/compiler.inc

## Detect architecture ##
. ./lib/sh/arch.inc

## Options ##
if [ $# -eq 1 ]; then
	if [ "${1}" == "fsma" ]; then
		echo "-DUSE_LIBFSMA" > .ecflags
		echo "-lfsma" > .elflags
	fi
else
	touch .ecflags
	touch .elflags
fi

## Build ##
make

if [ $? -ne 0 ]; then
	echo "Build failed."
	exit 1
fi

touch .done

echo "Build completed."

exit 0

