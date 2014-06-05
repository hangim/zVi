@echo off

gcc string.c    -c -std=c99 -Wall
gcc line.c      -c -std=c99 -Wall
gcc view.c      -c -std=c99 -Wall
gcc view_test.c -c -std=c99 -Wall

gcc string.o line.o view.o view_test.o -o view_test -std=c99 -Wall

del string.o line.o view.o view_test.o

view_test