/**
 * return_str.c -- перезаписывает строку на своё место при смене местоположения курсора
 *(чтобы в выводе текста на экран фигурировал один курсор)
 * Copyright (c) 2020 , Menshikov Mikhail
 *
 * This code is licensed under a MIT-style license.
 */

#include "_text.h"


void return_str(text txt, const char *str)
{
    if (str[0] != '\0')
        strcpy(txt->cursor->line->contents, str);

}
