#include "glwidget.hpp"
#include <QDebug>

void GLWidget::initialize (void)
{
    // initialize the widget, camera and light trackball, and opens default mesh
    Tucano::QtTrackballWidget::initialize();
    Tucano::QtTrackballWidget::openMesh("../samples/models/toy.ply");

    // initialize the shader effect
    ssrt.setShadersDir("../effects/shaders/");
    ssrt.initialize();
}

void GLWidget::paintGL (void)
{
    makeCurrent();

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    ssrt.render(mesh, camera, light_trackball);

    camera.render();
}
