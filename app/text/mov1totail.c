/**
 * mov1totail.c -- перемещаем первую строку в конец текста
 * 
 * Copyright (c) 2020 Menshikov Mikhail
 *
 * This code is licensed under a MIT-style license.
 */

#include "_text.h"

void mov1totail(text txt)
{

/* Проверяем, имеется ли текст */
if (txt == NULL || txt->length == 0)
    return;

/*указываем новое начало текста*/
    node *old_head = txt->begin;
    node *new_head = txt->begin->next;


/*расставлем указатели для нового начала текста*/
    txt->begin = new_head;
    txt->begin->previous = NULL;

/*расставляем указатели для нового конца текста*/
    char* ach;
    int pos;

    if((ach=strchr(txt->end->contents,'\0'))!=NULL){
        pos=ach-txt->end->contents;
        txt->end->contents[pos]='\n';
     }

    txt->end->next = old_head;
    old_head->next = NULL;
    old_head->previous = txt->end;
    txt->end = old_head;

    if((ach=strchr(txt->end->contents,'\n'))!=NULL){
        pos=ach-txt->end->contents;
        txt->end->contents[pos]='\0';
     }

}
