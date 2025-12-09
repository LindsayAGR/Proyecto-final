QT += core gui widgets multimedia


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    asteroide.cpp \
    astronauta.cpp \
    main.cpp \
    nivel2.cpp \
    nivel3.cpp \
    widget.cpp\
    panel.cpp\
    cohete.cpp

HEADERS += \
    asteroide.h \
    astronauta.h \
    nivel2.h \
    nivel3.h \
    widget.h\
    panel.h\
    cohete.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    recursos.qrc
