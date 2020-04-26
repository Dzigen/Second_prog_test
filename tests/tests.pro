include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

QMAKE_CXXFLAGS += -Wall -Wextra -Werror
QMAKE_CFLAGS += -Wall -Wextra -Werror

# gcov
QMAKE_CXXFLAGS +=-fprofile-arcs -ftest-coverage
QMAKE_CFLAGS +=-fprofile-arcs -ftest-coverage
LIBS +=-lgcov

INCLUDEPATH += ../app

SOURCES += \
    ../app/load.c \
    ../app/save.c \
    ../app/show.c \
    ../app/showlineswithdigits.c \
    ../app/text/append_line.c \
    ../app/text/create_text.c \
    ../app/text/cursor_insert_totail.c \
    ../app/text/cursor_loc_insert.c \
    ../app/text/mov1totail.c \
    ../app/text/process_forward.c \
    ../app/text/remove_all.c \
    ../app/text/return_str.c \
    main.cpp

HEADERS += \
    ../app/common.h \
    ../app/text/_text.h \
    ../app/text/text.h \
    c1n_test.h \
    m_test.h \
    mle_test.h \
    save_test.h \
    showlineswithdigits_test.h
