#!/bin/bash

if [[ -z "${CC}" ]]
then
  COMP="cc"
else
  COMP=${CC}
fi

clang ${CFLAGS} -Wall -Wextra -Wpedantic -Wno-implicit-fallthrough -std=gnu11 src/unity.c -o gcode.bin ${LDFLAGS} -lm -lX11 -lGLX
strip gcode.bin
