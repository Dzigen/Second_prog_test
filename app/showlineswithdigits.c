/**
 * showlineswithdigits.c -- для вывода текста строк, в которых встречаются цифры
 *
 * Copyright (c) 2020, Menshikov Mikhail
 *
 * This code is licensed under a MIT-style license.
 */
#include <stdio.h>
#include<string.h>
#include "common.h"
#include "text/text.h"

static void find_digit(int index, char *contents, int cursor, void *data);

void showlineswithdigits(text txt)
{
    FILE* buf=fopen("buffer.txt","w");
    process_forward(txt, find_digit, buf);
    fclose(buf);
}

static void find_digit(int index, char *contents, int cursor, void *data)
{
    UNUSED(index);
    UNUSED(cursor);
    if (strpbrk(contents, "0123456789") != 0){
        printf("%s", contents);
        fprintf(data,"%s", contents);
    }
}
