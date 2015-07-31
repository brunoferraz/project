#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/glew.h>

#include <QWidget>
#include <phongshader.hpp>
#include <utils/qtflycamerawidget.hpp>
#include <utils/qttrackballwidget.hpp>
#include <photo/photomesh.h>
#include <QImage>
#include <rendertexture.hpp>

class GLWidget : public Tucano::QtTrackballWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent);
    ~GLWidget();

    Effects::Phong phong;
    PhotoMesh photoMesh;
    Tucano::Camera calibrationCamera;
    Mesh backgroud;

    int currentCamera;

    void initialize();
    void paintGL();
    inline void nextCamera(){changeCamera(1);}
    inline void prevCamera(){changeCamera(-1);}

signals:
private:
    void changeCamera(int c);

    Effects::RenderTexture renderTexture;
    Texture image_Texture;

public slots:
};

#endif // GLWIDGET_H
