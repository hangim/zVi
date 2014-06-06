/******************************************************************************
 *
 * Filename:
 *  line.c
 *
 * Description:
 *   行相关
 *
 ******************************************************************************/

#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "line.h"

/******************************************************************************
 *
 * Function:
 *  Line_create
 *
 * Description:
 *  创建一行
 *
 * Params:
 *  无
 *
 * Input:
 *  无
 *
 * Output:
 *  无
 *
 * Return:
 *  行指针
 *
 ******************************************************************************/
struct Line *Line_create() {
    struct Line * line = (struct Line *) malloc(sizeof(struct Line));
    if (line == NULL) {
        perror("Line_create malloc failed\n");
        exit(1);
    }

    line->index = 0;
    line->string = NULL;
    line->next = NULL;

    return line;
}

/******************************************************************************
 *
 * Function:
 *  Line_set_index
 *
 * Description:
 *  设置行号
 *
 * Params:
 *  line:
 *      行指针
 *  index:
 *       行号
 *
 * Input:
 *  无
 *
 * Output:
 *  无
 *
 * Return:
 *  无
 *
 ******************************************************************************/
void Line_set_index(struct Line * const line, const int index) {
    if (line == NULL)
        return;
    line->index = index;
}

/******************************************************************************
 *
 * Function:
 *  Line_set_text
 *
 * Description:
 *  设置行文本
 *
 * Params:
 *  line:
 *      行指针
 *  buf:
 *       文本缓冲区
 *
 * Input:
 *  无
 *
 * Output:
 *  无
 *
 * Return:
 *  无
 *
 ******************************************************************************/
void Line_set_text(struct Line * const line, const char *buf) {
    if (line == NULL)
        return;

    String_destory(line->string);
    line->string = String_create(buf);
}

/******************************************************************************
 *
 * Function:
 *  Line_create_with_text
 *
 * Description:
 *  创建包含行文本的一行
 *
 * Params:
 *  buf:
 *       文本缓冲区
 *
 * Input:
 *  无
 *
 * Output:
 *  无
 *
 * Return:
 *  行指针
 *
 ******************************************************************************/
struct Line *Line_create_with_text(const char *buf) {
    struct Line *line = Line_create();
    Line_set_text(line, buf);

    return line;
}

/******************************************************************************
 *
 * Function:
 *  Line_print
 *
 * Description:
 *  打印输出一行
 *
 * Params:
 *  line:
 *      行指针
 *
 * Input:
 *  无
 *
 * Output:
 *  行文本
 *
 * Return:
 *  无
 *
 ******************************************************************************/
void Line_print(const struct Line * const line) {
    if (line == NULL)
        return;

    printf("%4d ", line->index);
    if (line->string == NULL)
        printf("\n");
    else
        String_print(line->string);
}

/******************************************************************************
 *
 * Function:
 *  Line_write
 *
 * Description:
 *  将一行写入文件
 *
 * Params:
 *  line:
 *      行指针
 *  fp:
 *      待写入文件指针
 *
 * Input:
 *  无
 *
 * Output:
 *  输出行文本到文件
 *
 * Return:
 *  无
 *
 ******************************************************************************/
void Line_write(const struct Line * const line, FILE * const fp) {
    if (line == NULL or fp == NULL)
        return;

    String_write(line->string, fp);
}

/******************************************************************************
 *
 * Function:
 *  Line_destory
 *
 * Description:
 *  销毁一行
 *
 * Params:
 *  line:
 *      行指针
 *
 * Input:
 *  无
 *
 * Output:
 *  无
 *
 * Return:
 *  无
 *
 ******************************************************************************/
void Line_destory(struct Line * const line) {
    String_destory(line->string);
    free(line);
}
