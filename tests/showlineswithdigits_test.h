#ifndef SHOWLINESWITHDIGITS_TEST_H
#define SHOWLINESWITHDIGITS_TEST_H
#include <gtest/gtest.h>

extern "C" {
#include "text/_text.h"
#include "common.h"
}

TEST(ShowLinesWithDigits,PositiveTest_FileWithDigitsLines){

    char buffername[20]="buffer.txt";
    FILE* buffer;
    char outBuffer[255];

    /*заполняем структуры строковым текстом*/
    text txt = create_text();
    remove_all(txt);
    append_line(txt, "qwert4uiop\n");
    append_line(txt, "adghjklzx\n");
    append_line(txt, "ad6ghjklzx\0");

    showlineswithdigits(txt);

    /*открываем buffer.txt для проверки выводимого текста*/
    buffer=fopen(buffername,"r");

    fgets(outBuffer,255, buffer);
        ASSERT_STREQ(outBuffer, "qwert4uiop\n");
    fgets(outBuffer,255, buffer);
        ASSERT_STREQ(outBuffer, "ad6ghjklzx\0");

    fclose(buffer);

    /*удаляем файл buffer.txt*/
    remove(buffername);

    free(txt);
}

TEST(ShowLinesWithDigits,NegativeTest_FileWithNoDigitsLines){
    char buffername[20]="buffer.txt";
    FILE* buffer;

    /*заполняем структуры строковым текстом*/
    text txt = create_text();
    remove_all(txt);
    append_line(txt, "qwertuiop\n");
    append_line(txt, "adghjklzx\n");
    append_line(txt, "adghjklzx\0");

    showlineswithdigits(txt);

    /*открываем buffer.txt для проверки выводимого текста*/
    buffer=fopen(buffername,"r");

    char chr=getc(buffer);
    ASSERT_EQ(chr, EOF);

    fclose(buffer);

    /*удаляем файл buffer.txt*/
    remove(buffername);

    free(txt);


}

TEST(ShowLinesWithDigits,NegativeTest_EmptyFile){

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

    showlineswithdigits(txt);

    /*открываем buffer.txt для проверки вывода сообщения об отсутствии строк для работы функции showlineswithdigits*/
    buffer=fopen(buffername,"r");

    while(fgets(outBuffer,255, buffer))
        for(int i=0;i<53;i++)
            ASSERT_EQ(outBuffer[i],errorMessage[i]);

    fclose(buffer);

    /*удаляем buffer.txt и input.txt*/
    remove(inputname);
    remove(buffername);

    free(txt);

}

#endif // SHOWLINESWITHDIGITS_TEST_H
