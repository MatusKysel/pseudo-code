#!/bin/sh

flex -l pseudo_code.l &&
bison -d pseudo_code.y &&
gcc *.c -o pseudo_code -Wall