@echo off

gcc string.c    -c -std=c99 -Wall
gcc line.c      -c -std=c99 -Wall
gcc view.c      -c -std=c99 -Wall
gcc zVi.c -c    -std=c99 -Wall

gcc string.o line.o view.o zVi.o -o zVi -std=c99 -Wall

del string.o line.o view.o zVi.o
