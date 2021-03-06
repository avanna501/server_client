QT += core gui
QT += network

#requires(qtConfig(combobox))
greaterThan(QT_MAJOR_VERSION, 4): QT +=widgets
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES +=  client.cpp \
            download.cpp \
            main.cpp \
            widget.cpp

HEADERS += client.h \
    download.h \
    widget.h

FORMS += \
    widget.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
