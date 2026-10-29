QT += core gui widgets testlib
CONFIG += console c++17
TEMPLATE = app
TARGET = calculator_demo
SOURCES += demo.cpp ../mainwindow.cpp ../calculatorengine.cpp
HEADERS += ../mainwindow.h ../calculatorengine.h
FORMS += ../calculator.ui
