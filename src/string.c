/******************************************************************************
 *
 * Filename:
 *  string.c
 *
 * Description:
 *  字符块链表相关
 *
 ******************************************************************************/

#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "string.h"

/******************************************************************************
 *
 * Function:
 *  String_create_node
 *
 * Description:
 *  创建一个字符块节点
 *
 ******************************************************************************/
struct String *String_create_node(const char * const buf) {
    struct String *s = (struct String *) malloc(sizeof(struct String));
    if (s == NULL) {
        perror("String_create_node malloc failed\n");
        exit(1);
    }
    
    if (buf == NULL) { // head node
        s->s = NULL;
    } else {
        s->s = (char *) malloc(STRING_MAX_SIZE + 1);
        if (s->s == NULL) {
            perror("String_create_node malloc failed\n");
            exit(1);
        }
        strncpy(s->s, buf, STRING_MAX_SIZE);
        s->s[STRING_MAX_SIZE] = '\0';
    }
    
    s->next = NULL;

    return s;
}

/******************************************************************************
 *
 * Function:
 *  String_create
 *
 * Description:
 *  创建一个字符块链表
 *
 ******************************************************************************/
struct String *String_create(const char *buf) {
    if (buf == NULL)
        return NULL;

    int len = strlen(buf);
    struct String *head, *p;
    head = p = String_create_node(NULL);

    while (len > 0) {
        p->next = String_create_node(buf);
        len -= STRING_MAX_SIZE;
        buf += STRING_MAX_SIZE;
        p = p->next;
    }

    return head;
}

/******************************************************************************
 *
 * Function:
 *  String_print
 *
 * Description:
 *  将一个字符块链表打印输出
 *
 ******************************************************************************/
void String_print(const struct String * const head) {
    if (head == NULL)
        return;

    struct String const *p = head;

    while (p->next) {
        printf("%s", p->next->s);
        p = p->next;
    }
}

/******************************************************************************
 *
 * Function:
 *  String_write
 *
 * Description:
 *  将一个字符块链表输出到文件
 *
 ******************************************************************************/
void String_write(const struct String * const head, FILE * const fp) {
    if (head == NULL or fp == NULL)
        return;

    struct String const *p = head;

    while (p->next) {
        fprintf(fp, "%s", p->next->s);
        p = p->next;
    }
}

/******************************************************************************
 *
 * Function:
 *  String_destory
 *
 * Description:
 *  销毁一个字符块链表
 *
 ******************************************************************************/
void String_destory(struct String * const head) {
    if (head == NULL)
        return;

    struct String *p, *q;
    p = q = head;
    while (p) {
        q = p->next;
        free(p->s);
        free(p);
        p = q;
    }
}
