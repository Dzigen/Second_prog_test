#ifndef M_TEST_H
#define M_TEST_H
#include <gtest/gtest.h>

extern "C" {
#include "text/_text.h"
#include "common.h"
}

TEST(PositiveTest_M,CorrectInput){

    char buffername[20]="buffer.txt";
    FILE* buffer;

    char outBuffer[255];
    char str[MAXLINE + 1] = "\0";

    /*заполняем структуры строковым текстом*/
    text txt = create_text();
    remove_all(txt);
    append_line(txt, "1111111111\n");
    append_line(txt, "22222222222\n");
    append_line(txt, "33333333333\0");

    cursor_loc_insert(txt,str,1,1);
    show(txt);

    buffer=fopen(buffername,"r");

    node* current=txt->begin;

    while(fgets(outBuffer,255,buffer)){
        for(int i=0;i<12;i++)
            ASSERT_EQ(outBuffer[i],current->contents[i]);
        current=current->next;
    }
    fclose(buffer);

    remove(buffername);

    remove_all(txt);

}

TEST(NegativeTest_M,OutOfRange_Up){
    char buffername[20]="buffer.txt";
    FILE* buffer;

    char outBuffer[255];
    char str[MAXLINE + 1] = "\0";

    /*заполняем структуры строковым текстом*/
    text txt = create_text();

    remove_all(txt);
    append_line(txt, "1111111111\n");
    append_line(txt, "2222222222\n");
    append_line(txt, "3333333333\0");

    /*проврека на работу при выбре строки за верхней грнаницей*/
    cursor_loc_insert(txt,str,-20,2);
    show(txt);

    buffer=fopen(buffername,"r");

     node* current=txt->begin;

    while(fgets(outBuffer,255,buffer)){
        for(int i=0;i<11;i++)
            ASSERT_EQ(outBuffer[i],current->contents[i]);
        current=current->next;
    }

    fclose(buffer);

    return_str(txt,str);

    /*проврека на работу при выбре строки за нмжней грнаницей*/
    cursor_loc_insert(txt,str,20,2);
    show(txt);

    buffer=fopen(buffername,"r");

    current=txt->begin;

    while(fgets(outBuffer,255,buffer)){
         for(int i=0;i<11;i++)
             ASSERT_EQ(outBuffer[i],current->contents[i]);
             current=current->next;
     }

    fclose(buffer);

    remove(buffername);

    remove_all(txt);
}

TEST(NegativeTest_M,CorrectInput_LeftRight){
    char buffername[20]="buffer.txt";
    FILE* buffer;

    char outBuffer[255];
    char str[MAXLINE + 1] = "\0";

    /*заполняем структуры строковым текстом*/
    text txt = create_text();

    remove_all(txt);
    append_line(txt, "11111111111\n");
    append_line(txt, "2222222222\n");
    append_line(txt, "33333333333\0");

    /*проврека на работу при выбре строки за правой грнаницей*/
    cursor_loc_insert(txt,str,2,20);
    show(txt);

    buffer=fopen(buffername,"r");

     node* current=txt->begin;

    while(fgets(outBuffer,255,buffer)){
        for(int i=0;i<11;i++)
            ASSERT_EQ(outBuffer[i],current->contents[i]);
        current=current->next;
    }

    fclose(buffer);

    return_str(txt,str);

    /*проврека на работу при выбре строки за левой грнаницей*/
    cursor_loc_insert(txt,str,2,-20);
    show(txt);

    buffer=fopen(buffername,"r");

    current=txt->begin;

    while(fgets(outBuffer,255,buffer)){
         for(int i=0;i<11;i++)
             ASSERT_EQ(outBuffer[i],current->contents[i]);
             current=current->next;
     }

    fclose(buffer);

    remove(buffername);

    remove_all(txt);


}

TEST(NegativeTest_M,EmptyFile){
    char inputname[20]="input.txt";
    FILE* input;
    char buffername[20]="buffer.txt";
    FILE* buffer;
    char string[255]="\0";

    char outBuffer[255];
    char errorMessage[255]="Downloaded file is empty.You cannot use this command";

    /*создаём структуры для пустого текста*/
    text txt = create_text();

    /*создаём пустой файл для загрузки*/
    input=fopen(inputname,"w");
    fclose(input);

    load(txt,inputname);
    cursor_loc_insert(txt,string,20,20);
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

#endif // M_TEST_H
