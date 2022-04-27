QT += core gui
QT += widgets
QT += network
#requires(qtConfig(combobox))

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES +=  client.cpp \
            main.cpp

HEADERS += client.h

FORMS += \
    dialog.ui
