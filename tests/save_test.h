#ifndef SAVE_TEST_H
#define SAVE_TEST_H

#include <gtest/gtest.h>

extern "C" {
#include "text/_text.h"
#include "common.h"
}

TEST(SaveFile,PositiveTest_NotEmptyFile){

    char filename[20]="output.txt";
    FILE* output;
    char outBuffer[255];
    int outputCount;

    /*заполняем структуры строковым текстом*/
    text txt = create_text();
    remove_all(txt);
    append_line(txt, "qwertyuiop\n");
    append_line(txt, "adfghjklzx\0");

    /*создаём файл для сохранения данных*/
    output=fopen(filename,"w");
    fclose(output);

    /*сохраняем текст в output.txt*/
    save(txt,filename);

    /*открываем output.txt для проверки сохранённого текста*/
    output=fopen(filename,"r");

    node* current = txt->begin;
    do {
    outputCount = fputs(outBuffer, output);
    for (int i = 0; i < outputCount; i++)
        ASSERT_EQ(outBuffer[i], current->contents[i]);
    current=current->next;
    } while (outputCount > 0);

    fclose(output);

    remove(filename);
    free(txt);
}

#endif // SAVE_TEST_H
