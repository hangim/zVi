@echo off

gcc string.c    -c -std=c99 -Wall
gcc line.c      -c -std=c99 -Wall
gcc line_test.c -c -std=c99 -Wall

gcc string.o line.o line_test.o -o line_test -std=c99 -Wall

del string.o line.o line_test.o

line_test