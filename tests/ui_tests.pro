QT += core gui widgets testlib
CONFIG += console testcase c++17
TEMPLATE = app
TARGET = ui_tests
SOURCES += ui_tests.cpp ../mainwindow.cpp ../calculatorengine.cpp
HEADERS += ../mainwindow.h ../calculatorengine.h
FORMS += ../calculator.ui
