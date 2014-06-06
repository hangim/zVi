/******************************************************************************
 *
 * Filename:
 *  zVi.h
 *
 * Description:
 *   主文件所需头文件
 *
 ******************************************************************************/

#ifndef zVi_MAIN
#define zVi_MAIN

#include "view.h"

void zVi_help();
void zVi_insert();
void zVi_delete();
void zVi_print();
void zVi_next_page();
void zVi_quit();

#define COMMAND_SIZE 320
char buf[COMMAND_SIZE + 1];

FILE *f_from;
FILE *f_to;
struct View *view;

#endif
