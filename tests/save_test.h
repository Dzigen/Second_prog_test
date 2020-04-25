#ifndef SAVE_TEST_H
#define SAVE_TEST_H

#include <gtest/gtest.h>
extern "C" {
#include "text/_text.h"
#include "common.h"
#include<stdio.h>
}

TEST(SaveFile,PositiveTest_NotEmptyFile){

    char filename[20]="output.txt";
    FILE* output;
    char outBuffer[255];

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

    while(fgets(outBuffer,255, output)){
        ASSERT_STREQ(outBuffer, current->contents);
         current=current->next;
    }

    /*закрываем и удаляем файл output.txt*/
    fclose(output);
    remove(filename);

    free(txt);
}

TEST(SaveFile,EmptyFile){

    char inputfile[20]="input.txt";
    FILE* input;
    char outputfile[20]="output.txt";
    FILE* output;
    char buffername[20]="buffer.txt";
    FILE* buffer;

    char outBuffer[255];
    char errorMessage[255]="Downloaded file is empty.You cannot use this command";

    /*создаём структуры для пустого текста*/
    text txt = create_text();

    /*создаём пустой файл для загрузки*/
    input=fopen(inputfile,"w");
    fclose(input);

    load(txt,inputfile);

    /*создаём файл для сохранения данных*/
    output=fopen(outputfile,"w");
    fclose(output);

    /*создаём файл для сохранения предупреждающего cообщения*/
    buffer=fopen(buffername,"w");
    int OldOut=dup(1);
    dup2(fileno(buffer),1);
    save(txt,outputfile);
    fclose(buffer);
    dup2(OldOut,1);

    /*открываем buffer.txt для проверки вывода сообщения о неодачном открытии файла output.txt*/
    buffer=fopen(buffername,"r");

    while(fgets(outBuffer,255, buffer))
        for(int i=0;i<53;i++)
            ASSERT_EQ(outBuffer[i],errorMessage[i]);

    fclose(buffer);

    /* удаляем output.txt,buffer.txt и input.txt*/
    remove(buffername);
    remove(outputfile);
    remove(inputfile);

    free(txt);

}

TEST(SaveFile,NegativeTest_NotExistingFile){

    char filename[20]="output.txt";
    char buffername[20]="buffer.txt";

    char outBuffer[255];
    char errorMessage[255]="The file output.txt cannot be opened";

    /*заполняем структуры строковым текстом*/
    text txt = create_text();
    remove_all(txt);
    append_line(txt, "qwertyuiop\n");
    append_line(txt, "adfghjklzx\0");

    FILE* buffer=fopen(buffername,"w");

    int oldoutput = dup(1);
    dup2(fileno(buffer),1);
    save(txt,filename);
    fclose(buffer);
    dup2(oldoutput,1);

    /*открываем buffer.txt для проверки вывода сообщения о неодачном открытии файла output.txt*/
    buffer=fopen(buffername,"r");

    while(fgets(outBuffer,255, buffer))
        for(int i=0;i<37;i++)
            ASSERT_EQ(outBuffer[i],errorMessage[i]);

    fclose(buffer);

    /* удаляем output.txt*/
    remove(buffername);

    free(txt);

}
#endif // SAVE_TEST_H
