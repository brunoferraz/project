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
    inline void nextCamera(){ photoMesh.nextPhoto();
                              photoMesh.calibrateCamera(calibrationCamera);
                              update();
                            }
    inline void prevCamera(){ photoMesh.prevPhoto();
                              photoMesh.calibrateCamera(calibrationCamera);
                              update();
                            }
signals:
private:
    Effects::RenderTexture renderTexture;
    Texture image_Texture;

public slots:
};

#endif // GLWIDGET_H
