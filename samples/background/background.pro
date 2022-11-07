TARGET = qgeoview-samples-background
TEMPLATE = app
CONFIG-= console

include(../../lib/lib.pri)

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h
