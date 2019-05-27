#-------------------------------------------------
#
# Project created by QtCreator 2019-05-19T11:07:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BiometricSystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    matchhandwriting.cpp \
    print_handwriting.cpp \
    verification.cpp \
    fusion_score.cpp \
    showperson.cpp

HEADERS += \
        mainwindow.h \
    verification.h \
    showperson.h

FORMS += \
        mainwindow.ui \
    verification.ui \
    showperson.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target




#Cuda
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/release/ -lafcuda
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/debug/ -lafcuda
else:unix: LIBS += -L$$PWD/../../../../usr/local/lib/ -lafcuda

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include





#Boost
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/release/ -lboost_system
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/debug/ -lboost_system
else:unix: LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/ -lboost_system





unix:!macx: LIBS += -L$$PWD/../../../../usr/local/lib/ -lopencv_world

INCLUDEPATH += $$PWD/../../../../usr/local/include/opencv4
DEPENDPATH += $$PWD/../../../../usr/local/include/opencv4




unix:!macx: LIBS += -L$$PWD/../../../../usr/local/lib/ -lUFMatcher

INCLUDEPATH += $$PWD/../../../../usr/local/include/suprema
DEPENDPATH += $$PWD/../../../../usr/local/include/suprema




unix:!macx: LIBS += -L$$PWD/../build-BiometricSystem-Desktop-Debug/ -lPreprocessing

INCLUDEPATH += $$PWD/../openfinger-preprocessor
DEPENDPATH += $$PWD/../openfinger-preprocessor



unix:!macx: LIBS += -L$$PWD/../build-BiometricSystem-Desktop-Debug/ -lMatcher

INCLUDEPATH += $$PWD/../openfinger-matcher
DEPENDPATH += $$PWD/../openfinger-matcher


unix:!macx: LIBS += -L$$PWD/../build-BiometricSystem-Desktop-Debug/ -lExtraction

INCLUDEPATH += $$PWD/../openfinger-extractor
DEPENDPATH += $$PWD/../openfinger-extractor




unix:!macx: LIBS += -L$$PWD/../build-BiometricSystem-Desktop-Debug/ -lcudart

INCLUDEPATH += $$PWD/../../../../usr/local/cuda/include
DEPENDPATH += $$PWD/../../../../usr/local/cuda/include
