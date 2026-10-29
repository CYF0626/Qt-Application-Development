QT += core testlib
QT -= gui
CONFIG += console testcase c++17
CONFIG -= app_bundle
TEMPLATE = app
TARGET = engine_tests
SOURCES += engine_tests.cpp ../calculatorengine.cpp
HEADERS += ../calculatorengine.h
