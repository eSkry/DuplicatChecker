include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG += qt

INCLUDEPATH += ../../

HEADERS += \
        duplicatchechertestclass.h \
        tst_duplicatfinder.h \
        ../../duplicatfinder.h

SOURCES += \
        duplicatchechertestclass.cpp \
        main.cpp \
        ../../duplicatfinder.cpp
