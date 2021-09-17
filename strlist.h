#pragma once

typedef struct
{
    unsigned int size; //子字符串数量
    char **list;       //用字符串数组来存放字符串列表
} st_strlist;

st_strlist *strlist_malloc();
int strlist_push(st_strlist *strlist, char *fmt, ...);
int strlist_add(st_strlist *strlist, char *str);
int strlist_insertAfter(st_strlist *strlist, char *str, unsigned int index);
int strlist_removeLast(st_strlist *strlist);
int strlist_removeAt(st_strlist *strlist, unsigned int index);
char *strlist_getStrAt(st_strlist *strlist, unsigned int index);
int strlist_contains(st_strlist *strlist, char *str);
int strlist_free(st_strlist *strlist);
void strlist_infolog(st_strlist *strlist);