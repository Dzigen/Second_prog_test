TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    editor.c \
    load.c \
    save.c \
    show.c \
    showlineswithdigits.c \
    text/append_line.c \
    text/create_text.c \
    text/cursor_loc_insert.c \
    text/mov1totail.c \
    text/process_forward.c \
    text/remove_all.c \
    text/return_str.c

HEADERS += \
    common.h \
    text/_text.h \
    text/text.h

QMAKE_CFLAGS += -Wall -Wextra -Werror

# gcov
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov
