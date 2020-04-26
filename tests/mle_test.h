#ifndef MLE_TEST_H
#define MLE_TEST_H
#include <gtest/gtest.h>

extern "C" {
#include "text/_text.h"
#include "common.h"
}


TEST(Mle,PositiveTest_CorrectInsert){
    char buffername[20]="buffer.txt";
    FILE* buffer;

    char outBuffer[255];
    char str[MAXLINE + 1] = "\0";

    /*заполняем структуры строковым текстом*/
    text txt = create_text();
    remove_all(txt);
    append_line(txt, "1111111111\n");
    append_line(txt, "2222222222\0");

    /*ставим курсор во внутреннюю строку текста*/
    cursor_loc_insert(txt,str,1,1);
    return_str(txt,str);
    cursor_insert_totail(txt);
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

    /*ставим курсор в конец текста*/
    cursor_loc_insert(txt,str,2,1);
    return_str(txt,str);
    cursor_insert_totail(txt);
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

TEST(Mle,NegativeTest_NotCorrectInsert){
    char buffername[20]="buffer.txt";
    FILE* buffer;

    char outBuffer[255];
    char str[MAXLINE + 1] = "\0";
    char errorMessage[30]="Usage: have no basis line";

    /*заполняем структуры строковым текстом*/
    text txt = create_text();
    remove_all(txt);
    append_line(txt, "1111111111\n");
    append_line(txt, "22222222222\n");
    append_line(txt, "33333333333\0");

    if (str[0] == '\0') {
        fprintf(stderr, "Usage: have no basis line");

        FILE* buf=fopen("buffer.txt","w");
        fputs("Usage: have no basis line",buf);
        fclose(buf);
    }else {
        cursor_insert_totail(txt);
        show(txt);
        }

    buffer=fopen(buffername,"r");

    while(fgets(outBuffer,255,buffer)){
        ASSERT_STREQ(outBuffer,errorMessage);
        for(int i=0;i<12;i++)
            ASSERT_EQ(outBuffer[i],errorMessage[i]);
    }

    fclose(buffer);

    remove(buffername);

    remove_all(txt);

}

TEST(Mle,NegativeTest_EmptyFile){
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
    cursor_insert_totail(txt);
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


#endif // MLE_TEST_H
