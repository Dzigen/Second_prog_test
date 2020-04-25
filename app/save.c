/**
 * save.c -- реализует команду cохранения  отредактированног  текста в файл
 *
 * Copyright (c) 2020, Menshikov Mikhail
 *
 * This code is licensed under a MIT-style license.
 */
#include <stdio.h>
#include "common.h"
#include "text/text.h"
#include <assert.h>

static void save_line(int index, char *contents, int cursor, void *data);

/**
 * Сохраняем отредактированный текст в файла
 */
void save(text txt, char *filename)
{

    FILE *f;
    /* Открываем файл для чтения, контролируя ошибки */
    if ((f = fopen(filename, "w")) == NULL) {
        printf("The file %s cannot be opened\n", filename);
        return;
    }

    process_forward(txt, save_line, f);


    fclose(f);
}

/**
 * Выводит содержимое указанного файла на экран
 */
static void save_line(int index, char *contents, int cursor, void *data)
{
    assert(contents != NULL);

    /* Декларируем неиспользуемые параметры */
    UNUSED(index);
    UNUSED(cursor);
    /*ведём запись пока не дойдём до концв списка */
    fputs(contents, data);

}
