#-------------------------------------------------
#
# Project created by QtCreator 2014-03-14T19:22:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TAI_MI
TEMPLATE = app


SOURCES += main.cpp\
        fenetreprincipale.cpp \
    automate.cpp \
    etat.cpp \
    transition.cpp \
    analysesyntaxique.cpp

HEADERS  += fenetreprincipale.h \
    automate.h \
    etat.h \
    transition.h \
    analysesyntaxique.h

FORMS    += fenetreprincipale.ui

# CIBLE DU PROGRME

Release:DESTDIR = Build
Release:OBJECTS_DIR = Build/.obj
Release:MOC_DIR = Build/.moc
Release:RCC_DIR = Build/.rcc
Release:UI_DIR = Build/.ui

Debug:DESTDIR = Build
Debug:OBJECTS_DIR = Build/.obj
Debug:MOC_DIR = Build/.moc
Debug:RCC_DIR = Build/.rcc
Debug:UI_DIR = Build/.ui
