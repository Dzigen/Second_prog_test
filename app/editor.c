/**
 * editor.c -- строковый текстовый редактор
 * 
 * Copyright (c) 2017, Alexander Borodin <aborod@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text/text.h"
#include "common.h"

#define MAXLINE 255

int main()
{
    char cmdline[MAXLINE + 1];
    char *cmd;

    char *arg;
    char *arg1;
    int arg2;
    int arg3;

    /*флаг для подмены строк */
    int flag = 1;
    /*храним  исходную строку , где вставлен курсор */
    char str[MAXLINE + 1] = "\0";

    /* Создаем объект для представления текста */
    text txt = create_text();

    /* Цикл обработки команд */
    while (1) {
        printf("\ned > ");

        /* Получаем команду */
       if(fgets(cmdline, MAXLINE, stdin)==NULL){
           printf("Cannot read this command.Try again.");
           continue;
       }
        /* Извлекаем имя команды */
        if ((cmd = strtok(cmdline, " \n")) == NULL) {
            continue;
        }

        /* Распознаем поддерживаемую команду */

        /* Завершаем работу редактора */
        if (strcmp(cmd, "quit") == 0) {

            /*если использовался вывод курсора,то заменяем строку на исходную */
            if (str[0] != '\0')
                return_str(txt, str);
            remove_all(txt);
            fprintf(stderr, "Bye!\n");
            break;
        }

        /* Загружаем содержимое файла, заданного параметром */
        if (strcmp(cmd, "load") == 0) {
            if ((arg = strtok(NULL, " \n")) == NULL) {
                fprintf(stderr, "Usage: load filename\n");
            } else {
                load(txt, arg);
            }
            continue;
        }

        /*Ставит первую строку в конец текстового файла */
        if (strcmp(cmd, "c1n") == 0) {
            if (str[0] != '\0')
                return_str(txt, str);
            mov1totail(txt);
            show(txt);
            continue;
        }

        if (strcmp(cmd, "showlineswithdigits") == 0) {
            showlineswithdigits(txt);
            continue;
        }


        /* ставим курсор в заданную позицию arg-строка,arg1-позиция в строке */
        if (strcmp(cmd, "m") == 0) {
            if (((arg = strtok(NULL, " ")) == NULL)
                || ((arg1 = strtok(NULL, " \n")) == NULL)) {
                fprintf(stderr, "Usage: loss arguments\n");
            } else {
                if (flag == 1)
                    flag = 0;
                else {
                    return_str(txt, str);
                }
                arg2 = atoi(arg);
                arg3 = atoi(arg1);
                cursor_loc_insert(txt, str, arg2, arg3);
                show(txt);
            }
            continue;
        }

        if (strcmp(cmd, "mle") == 0) {
            if (str[0] == '\0') {
                fprintf(stderr, "Usage: have no basis line");

                FILE* buf=fopen("buffer.txt","w");
                fputs("Usage: have no basis line",buf);
                fclose(buf);
            } else {
                if (flag == 1)
                    flag = 0;
                else {
                    return_str(txt, str);
                }
                cursor_insert_totail(txt);
                show(txt);
            }
            continue;
        }

        /* Выводим текст */
        if (strcmp(cmd, "show") == 0) {
            show(txt);
            continue;
        }

        /*сохраняем отредактированный текс в заданный файл */
        if (strcmp(cmd, "save") == 0) {
            if ((arg = strtok(NULL, " \n")) == NULL) {
                fprintf(stderr, "Usage: load filename\n");
            } else {

                if (str[0] != '\0') {
                    return_str(txt, str);
                    memset(str, '\0', MAXLINE + 1);
                }
                save(txt, arg);
            }
            continue;
        }

        /* Если команда не известна */
        fprintf(stderr, "Unknown command: %s\n", cmd);

    }

    remove("buffer.txt");
    return 0;
}
