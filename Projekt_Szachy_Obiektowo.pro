TEMPLATE = app
QT += gui widgets
CONFIG += c++11

SOURCES += main.cpp \
    CPion.cpp \
    CWieza.cpp \
    CKon.cpp \
    CSkoczek.cpp \
    CKrolowa.cpp \
    CKrol.cpp \
    CGra.cpp \
    CGlowneOkno.cpp \
    CPoleSzachownicy.cpp \
    CFigura.cpp \
    CSzachownica.cpp

HEADERS += \
    CPion.h \
    CWieza.h \
    CKon.h \
    CSkoczek.h \
    CKrolowa.h \
    CKrol.h \
    CGra.h \
    CGlowneOkno.h \
    CPoleSzachownicy.h \
    CFigura.h \
    CSzachownica.h

FORMS += \
    cglowneokno.ui

RESOURCES += \
    images.qrc


