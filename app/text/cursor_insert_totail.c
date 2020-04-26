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
    if(txt->cursor->line==NULL){
        fprintf(stderr, "Usage: have no basis line");
        return;
    }

    /*указатель на искомый символ*/
    const char* ach;
    /*позиция курсора в конце строки*/
    int pos;
    /*символ перевода на новую строку или конца строки*/
    char* sgnw="";

    if((ach=strchr(txt->cursor->line->contents,'\0'))!=NULL)
        sgnw="\0";
    if((ach=strchr(txt->cursor->line->contents,'\n'))!=NULL)
        sgnw="\n";


    pos=ach-txt->cursor->line->contents;
    txt->cursor->line->contents[pos]='|';
    txt->cursor->line->contents[pos+1]=*sgnw;

    txt->cursor->position=pos;

}
