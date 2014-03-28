#-------------------------------------------------
#
# Project created by QtCreator 2014-03-28T13:48:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Projet_TAI_MathInfo
TEMPLATE = app

SOURCES += main.cpp\
    Automate/analyseurSyntaxique.cpp

#############################################
# FICHIERS SOURCE QUI REPRESENTE L'AUTOMATE
#############################################
HEADERS  += Automate/automate.h \
    Automate/analyseurSyntaxique.h
HEADERS  += Automate/etat.h
HEADERS  += Automate/transition.h

SOURCES += Automate/automate.cpp
SOURCES += Automate/etat.cpp
SOURCES += Automate/transition.cpp

#############################################
# FICHIER DE L'INTERFACE GRAPHIQUE
#############################################
SOURCES +=  Gui/fenetrePrincipake.cpp
HEADERS  += Gui/fenetrePrincipake.h
FORMS    += Gui/fenetrePrincipake.ui

#############################################
# CIBLE DU PROGRME
#############################################
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
