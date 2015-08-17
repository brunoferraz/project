#-------------------------------------------------
#
# Project created by QtCreator 2015-07-22T15:14:31
#
#-------------------------------------------------

QT       += core gui opengl xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mscProject
TEMPLATE = app

EIGEN_PATH  =  /usr/local/include/eigen3

TUCANO_PATH = $$PWD/../tucano-master

BUILDDIR = $$TUCANO_PATH/../build/

LIBS += -lGLEW -lGLU

INCLUDEPATH +=  $$TUCANO_PATH/src $$TUCANO_PATH/effects $$EIGEN_PATH

OBJECTS_DIR =   $$BUILDDIR/obj
MOC_DIR =       $$BUILDDIR/moc
RCC_DIR =       $$BUILDDIR/rcc
UI_DIR =        $$BUILDDIR/ui
DESTDIR =       $$BUILDDIR/bin

QMAKE_CXXFLAGS += -DTUCANODEBUG

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    util/util.cpp \
    photo/photomesh.cpp \
    photo/photocamera.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    $$BUILDDIR/bin/effects/phongshader.hpp \
    $$BUILDDIR/build/bin/effects/rendertexture.hpp \
    $$TUCANO_PATH/src/utils/qttrackballwidget.hpp \
    util/util.h \
    photo/photomesh.h \
    photo/photocamera.h \
    $$TUCANO_PATH/src/utils/qtflycamerawidget.hpp

OTHER_FILES += $$BUILDDIR/bin/effects/shaders/rendertexture.vert \
               $$BUILDDIR/bin/effects/shaders/rendertexture.frag \
               $$BUILDDIR/bin/effects/shaders/phongshader.vert \
               $$BUILDDIR/bin/effects/shaders/phongshader.frag \

FORMS    += mainwindow.ui

