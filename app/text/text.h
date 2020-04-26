/**
 * text.h -- внешний интерфейс библиотеки для работы с текстом
 *
 * Copyright (c) 2017, Alexander Borodin <aborod@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#ifndef TEXT_H
#define TEXT_H

#define MAXLINE 255

/**
 * Абстрактный тип текстовых объектов
 */
typedef struct _list *text;

/**
 * Абстрактный тип курсора
 */
typedef struct _crsr *cursor;


/**
 * Создает новый текстовый объект
 * @returns текст
 */
text create_text();

/**
 * Добавляет одну строку к тексту
 * @param txt текст
 * @param contents новая строка
 * @returns none
 */
void append_line(text txt, const char *contents);


/**
 * Обрабатывает текст, применяя заданную функцию к каждой строке
 * 
 * @param txt текст
 * @param process функция-обработчик
 * @returns none
 */
void process_forward(
    text txt,
    void (*process)(int index, char *contents, int cursor_position, void *data),
    void *data
);


/**
 * Удаляет весь текст
 * 
 * @param txt текст
 * @returns none
 */
void remove_all(text txt);

/**
 * Изменяем позицию курсора
 * 
 * @param txt текст
 * @param line строка с курсором(нумерация начинается с единицы)
 * @param position расположение в строке(нумерация начинается с нуля)
 * @param string буфер для хранения исходной строки
 */
void cursor_loc_insert(text txt,char string[MAXLINE+1],int line,int position);

/**
 * Ставим курсор в конец строки
 *
 * @param txt текст
 */
void cursor_insert_totail(text txt);


/**
 * перезаписывает строку без курсора
 * 
 * @param txt текст
 * @str исходная строка текста
 * @returns none
 */
void return_str(text txt, char string[MAXLINE+1]);

/**
 * перезаписывает строку без курсора
 * 
 * @param txt текст
 * @param line_pos номер строки
 * @returns none
 */
void mov1totail(text txt);


#endif
