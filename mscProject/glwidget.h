#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/glew.h>

#include <QWidget>
#include <phongshader.hpp>
#include <utils/qtflycamerawidget.hpp>
#include <utils/qttrackballwidget.hpp>
#include <photo/photomesh.h>


class GLWidget : public Tucano::QtTrackballWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent);
    ~GLWidget();

    Effects::Phong phong;
    PhotoMesh photoMesh;
    Tucano::Camera calibrationCamera;

    void initialize();
    void paintGL();

signals:

public slots:
};

#endif // GLWIDGET_H
