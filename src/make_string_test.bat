@echo off
gcc string.c -c
gcc string_test.c -c
gcc string.o string_test.o -o string_test
del string.o string_test.o

string_test