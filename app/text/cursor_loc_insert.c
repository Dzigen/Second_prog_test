/**
 * cursoe_loc.c -- меняем координаты курсора в тексте и возвращает строку , в которую будет подставлен курсор
 *
 * Copyright (c) 2020, Menshikov Mikhail
 *
 * This code is licensed under a MIT-style license.
 */
#include "_text.h"

void cursor_loc_insert(text txt, char string[MAXLINE + 1], int line,
                       int position)
{
    /* Проверяем, имеется ли текст */
    if (txt == NULL || txt->length == 0)
        return;


    int len_string;

    /*перебираем возможные выбранные строки*/
    if(line<1)
        line=1;
    else if((size_t)line > txt->length)
        line=txt->length;

    /*добираемся до нужной строки */
    node *line_pos = txt->begin;

    for (int i = 1; i < line; i++) {
        if (line_pos->next == NULL)
            break;
        else
            line_pos = line_pos->next;
        }

    txt->cursor->line = line_pos;
    /*запоминаем строки перед изменением */
    strcpy(string, line_pos->contents);

    len_string = strlen(line_pos->contents);

    const char* sigw;
    int sign;
    /*перебираем возможные расположения курсора в строке */
    if (position > len_string) {
        if((size_t)line == txt->length){
            sigw="\0";
            sign='\0';
        }else{
            sigw="\n";
            sign='\n';
        }

         char* end_line=strchr(line_pos->contents,sign);
         *end_line = '|';
         txt->cursor->position = len_string;
         strcat(line_pos->contents, sigw);

    } else if (position <= 0) {
        txt->cursor->position = 0;
        char buf[MAXLINE + 1] = "|";
        strcat(buf, line_pos->contents);
        strcpy(line_pos->contents, buf);

    } else {
        txt->cursor->position = (position-1);

        char buf1[MAXLINE + 1] = "";
        strncat(buf1, line_pos->contents, (position-1));
        strcat(buf1, "|");
        strcat(buf1, line_pos->contents + (position-1));
        strcpy(line_pos->contents, buf1);

    }
}
