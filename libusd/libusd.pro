#-------------------------------------------------
#
# Project created by QtCreator 2019-02-05T11:07:41
#
#-------------------------------------------------
QT   += core
QT       -= gui

TARGET = usd
TEMPLATE = lib
CONFIG += staticlib
#DEFINES += LIBUSD_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        libusd.cpp \
    gpio/gpio.cpp \
    gpio/gpioclass.cpp \
    gpio/mmio.cpp \
    bh1750/bh1750.cpp \
    dht22/dht_read.cpp \
    dht22/dht_utils.cpp \
    serial_lcd/ili9341.cpp \
    serial_lcd/seriallcd.cpp \
    serial_lcd/virtuallcd.cpp \
    spi/bitbangspi.cpp \
    spi/spi.cpp

HEADERS += \
        libusd.h \
        libusd_global.h \
    bh1750/bh1750.h \
    dht22/dht_read.h \
    dht22/dht_utils.h \
    gpio/gpio.h \
    gpio/gpioclass.h \
    gpio/mmio.h \
    serial_lcd/seriallcd.h \
    spi/spi.h


unix {
    target.path = /usr/lib
    INSTALLS += target
}
