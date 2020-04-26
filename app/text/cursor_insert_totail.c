/**
 * cursoe_insert_totail.c --ставим курсор в конец строки
 *
 * Copyright (c) 2020, Menshikov Mikhail
 *
 * This code is licensed under a MIT-style license.
 */
#include "_text.h"

void cursor_insert_totail(text txt)
{
    /* Проверяем, имеется ли текст */
    if (txt == NULL || txt->length == 0)
        return;
    char* ach;
    int pos;

    if((ach=strchr(txt->cursor->line->contents,'\n'))!=NULL){
        pos=ach-txt->cursor->line->contents;
        txt->cursor->line->contents[pos+1]='\n';
     }else{
        ach=strchr(txt->cursor->line->contents,'\0');
        pos=ach-txt->cursor->line->contents;
        txt->cursor->line->contents[pos+1]='\0';
    }
            txt->cursor->line->contents[pos]='|';

    txt->cursor->position=pos;
}
