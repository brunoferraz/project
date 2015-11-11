#-------------------------------------------------
#
# Project created by QtCreator 2015-07-22T15:14:31
#
#-------------------------------------------------

QT       += core gui opengl xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mscProject
TEMPLATE = app

EIGEN_PATH  =  /usr/include/eigen3

TUCANO_PATH = $$PWD/../../tucano

BUILDDIR = $$PWD/../build/

LIBS += -lGLEW -lGLU

INCLUDEPATH +=  $$TUCANO_PATH/src $$TUCANO_PATH/effects $$EIGEN_PATH $$BUILDDIR/bin/effects

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
    photo/multiTextureManagerObj.cpp \
    photo/photocamera.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    $$BUILDDIR/bin/effects/rendertexture.hpp \
    $$TUCANO_PATH/src/utils/qttrackballwidget.hpp \
    util/util.h \
    photo/multiTextureManagerObj.h \
    photo/photocamera.h \
    $$TUCANO_PATH/src/utils/qtflycamerawidget.hpp \
    $$BUILDDIR/bin/effects/phongshader.hpp \
    $$BUILDDIR/bin/effects/multitextureshader.hpp \
    $$BUILDDIR/bin/effects/pingpong.hpp \

OTHER_FILES += $$BUILDDIR/bin/effects/shaders/rendertexture.vert \
               $$BUILDDIR/bin/effects/shaders/rendertexture.frag \
               $$BUILDDIR/bin/effects/shaders/phongshader.vert \
               $$BUILDDIR/bin/effects/shaders/phongshader.frag \
               $$BUILDDIR/bin/effects/shaders/showFbo.vert \
               $$BUILDDIR/bin/effects/shaders/showFbo.frag \
               $$BUILDDIR/bin/effects/shaders/multitextureshader.vert \
               $$BUILDDIR/bin/effects/shaders/multitextureshader.frag \
               $$BUILDDIR/bin/effects/shaders/pptf.vert \
               $$BUILDDIR/bin/effects/shaders/pptf.frag \

FORMS    += mainwindow.ui

