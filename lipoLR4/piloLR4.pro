TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    to_polish_notation.cpp \
    create_asm_by_polish.cpp

HEADERS += \
    to_polish_notation.h \
    create_asm_by_polish.h \
    find_operands_and_functions.h
