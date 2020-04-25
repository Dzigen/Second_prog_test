#ifndef SAVE_TEST_H
#define SAVE_TEST_H

#include <gtest/gtest.h>

extern "C" {
#include "text/_text.h"
#include "common.h"
}

TEST(SaveFile,PositiveTest_NotEmptyFile){

    /*заполняем структуры строковым текстом*/
    text txt = create_text();
    remove_all(txt);
    append_line(txt, "qwertyuiop\n");
    append_line(txt, "adfghjklzx\0");

    /*создаём файл для сохранения данных*/
    char filename[20]="output.txt";
    FILE* output;
    output=fopen(filename,"w");
    fclose(output);

    /*сохраняем текстовые данные в созданный файл*/
    save(txt,filename);

    /*открываем output.txt для проверки верного сохранения текста*/

    char outBuffer[255];
    output=fopen(filename,"r");
    int outputCount;

    node* current = txt->begin;

    do {
    outputCount = fputs(outBuffer, output);
    for (int i = 0; i < outputCount; i++)
        ASSERT_EQ(outBuffer[i], current->contents[i]);
    current=current->next;
    } while (outputCount > 0);


    /*закрываем и удаляем output.txt*/
    fclose(output);
    remove(filename);

}

TEST(SaveFile,NegativeTest_EmptyFile){

}

TEST(SaveFile,NegativeTest_NotExistingFile){
    /*   char buffername[20]="buffer.txt";
    FILE* buffer=fopen(buffername,"w");
    fclose(buffer);
     *
     * dup2(fileno(buffer),1);
    save(txt,filename);
     dup2(oldoutput,1);*/
}

#endif // SAVE_TEST_H
