QT += core
QT -= gui

CONFIG += c++11

TARGET = qt
CONFIG += console
CONFIG -= app_bundle

#Needed to link against pkg-builds output for opencv
CONFIG += link_pkgconfig
PKGCONFIG+=opencv

TEMPLATE = app

SOURCES += main.cpp
