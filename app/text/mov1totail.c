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

/*указываем новое начало текста*/
    node *old_head = txt->begin;
    node *new_head = txt->begin->next;


/*расставлем указатели для нового начала текста*/
    txt->begin = new_head;
    txt->begin->previous = NULL;

/*расставляем указатели для нового конца текста*/
    txt->end->next = old_head;
    old_head->next = NULL;
    old_head->previous = txt->end;
    txt->end = old_head;

}
