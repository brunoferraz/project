#ifndef __GLWIDGET__
#define __GLWIDGET__

#include <GL/glew.h>

#include <phongshader.hpp>
#include <ssrt.hpp>
#include <depthMap.hpp>
#include <utils/qttrackballwidget.hpp>
#include <framebuffer.hpp>

using namespace std;

class GLWidget : public Tucano::QtTrackballWidget
{
    Q_OBJECT

public:

    explicit GLWidget(QWidget *parent) : Tucano::QtTrackballWidget(parent) {}
    ~GLWidget() {}
    
    /**
     * @brief Initializes the shader effect
     * @todo remove hard coded mesh file!!
     */
    void initialize();

    /**
     * Repaints screen buffer.
     **/
    virtual void paintGL();

signals:
    
public slots:
    
private:

    Effects::Phong phong;
    Effects::DepthMap depthMap;
    Effects::SSRT ssrt;

};

#endif // GLWIDGET
