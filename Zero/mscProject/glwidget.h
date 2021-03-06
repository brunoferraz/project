#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/glew.h>

#include <QWidget>
#include <phongshader.hpp>
#include <utils/qtflycamerawidget.hpp>
#include <utils/qttrackballwidget.hpp>
#include <photo/multiTextureManagerObj.h>
#include <multitextureshader.hpp>
#include <multitexttf.hpp>
#include <pingpong.hpp>
#include <QImage>
#include <rendertexture.hpp>

class GLWidget : public Tucano::QtTrackballWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent);
    ~GLWidget();

    Effects::Phong phong;
    Effects::MultiTexture multi;
    Effects::PingPong pingpong;
    Effects::MultiTextTF multitexttf;

    MultiTextureManagerObj multitexture;
    Tucano::Camera calibrationCamera;
    Mesh backgroud;

    int currentCamera;

    void initialize();
    void paintGL();
    inline void nextCamera(){ multitexture.nextPhoto();
                              multitexture.calibrateCamera(calibrationCamera);
                              multitexture.calibrateCamera(camera);
                              update();
                            }
    inline void prevCamera(){ multitexture.prevPhoto();
                              multitexture.calibrateCamera(calibrationCamera);
                              multitexture.calibrateCamera(camera);
                              update();
                            }
signals:
private:
    Effects::RenderTexture renderTexture;
    Texture image_Texture;

public slots:
protected:
    void mouseReleaseEvent(QMouseEvent *ev);
};

#endif // GLWIDGET_H
