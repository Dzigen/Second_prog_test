#ifndef C1N_H
#define C1N_H
#include <gtest/gtest.h>

extern "C" {
#include "text/_text.h"
#include "common.h"
}

TEST(C1n,PositiveTest_NotEmptyFile){

    char buffername[20]="buffer.txt";
    FILE* buffer;

    char outBuffer[255];

    /*заполняем структуры строковым текстом*/
    text txt = create_text();
    remove_all(txt);
    append_line(txt, "1111111111\n");
    append_line(txt, "2222222222\n");
    append_line(txt, "3333333333\0");

    mov1totail(txt);
    show(txt);

    buffer=fopen(buffername,"r");
    node* current=txt->begin;

    while(fgets(outBuffer,255,buffer)){
        for(int i=0;i<11;i++)
            ASSERT_EQ(outBuffer[i],current->contents[i]);
        current=current->next;
    }

    fclose(buffer);

    remove(buffername);
    remove_all(txt);
}

TEST(C1n,NegativeTest_EmptyFile){

    char inputname[20]="input.txt";
    FILE* input;
    char buffername[20]="buffer.txt";
    FILE* buffer;

    char outBuffer[255];
    char errorMessage[255]="Downloaded file is empty.You cannot use this command";

    /*создаём структуры для пустого текста*/
    text txt = create_text();

    /*создаём пустой файл для загрузки*/
    input=fopen(inputname,"w");
    fclose(input);

    load(txt,inputname);
    mov1totail(txt);
    show(txt);

    /*открываем buffer.txt для проверки вывода сообщения об отсутствии строк для работы функции mov1totail*/
    buffer=fopen(buffername,"r");

    while(fgets(outBuffer,255, buffer))
        for(int i=0;i<53;i++)
            ASSERT_EQ(outBuffer[i],errorMessage[i]);

    fclose(buffer);

    /* удаляем input.txt и buffer.txt*/
    remove(inputname);
    remove(buffername);

    remove_all(txt);
}

#endif // C1N_H
