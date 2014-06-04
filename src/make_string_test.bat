@echo off

gcc string.c      -c  -std=c99 -Wall
gcc string_test.c -c  -std=c99 -Wall

gcc string.o string_test.o -o string_test -std=c99 -Wall

del string.o string_test.o

string_test