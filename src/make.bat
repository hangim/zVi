@echo off

gcc string.c -c -std=c99 -Wall -fexec-charset=GBK
gcc line.c   -c -std=c99 -Wall -fexec-charset=GBK
gcc view.c   -c -std=c99 -Wall -fexec-charset=GBK
gcc zVi.c    -c -std=c99 -Wall -fexec-charset=GBK

gcc string.o line.o view.o zVi.o -o zVi -std=c99 -Wall -fexec-charset=GBK

del string.o line.o view.o zVi.o
