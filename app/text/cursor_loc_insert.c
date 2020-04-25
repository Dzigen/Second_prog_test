/**
 * cursoe_loc.c -- меняем координаты курсора в тексте и возвращает строку , в которую подет подставлен курсор
 *
 * Copyright (c) 2020, Menshikov Mikhail
 *
 * This code is licensed under a MIT-style license.
 */
#include "_text.h"

void cursor_loc_insert(text txt, char string[MAXLINE + 1], int line,
                       int position)
{


    int len_string;


    /*добираемся до нужной строки */
    node *line_pos = txt->begin;

    if (line == -1 && position == -1) {
        line_pos = txt->cursor->line;
        position = 256;
    } else {
        for (int i = 1; i < line; i++) {
            if (line_pos->next == NULL)
                break;
            else
                line_pos = line_pos->next;
        }
    }

    txt->cursor->line = line_pos;
    /*запоминаем строки перед изменением */
    strcpy(string, line_pos->contents);

    len_string = strlen(line_pos->contents);

    /*перебираем возможные расположения курсора в строке */
    if (position > len_string) {
        char *end_line = strpbrk(line_pos->contents, "\n");
        *end_line = '|';
        txt->cursor->position = len_string;
        strcat(line_pos->contents, "\n");
    } else if (position <= 0) {
        txt->cursor->position = 0;
        char buf[MAXLINE + 1] = "|";
        strcat(buf, line_pos->contents);
        strcpy(line_pos->contents, buf);
    } else {
        txt->cursor->position = position;
        char buf1[MAXLINE + 1] = "";
        strncat(buf1, line_pos->contents, position);
        strcat(buf1, "|");
        strcat(buf1, line_pos->contents + position);
        strcpy(line_pos->contents, buf1);
    }
}
