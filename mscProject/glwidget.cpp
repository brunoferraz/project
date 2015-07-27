#include "glwidget.h"
GLWidget::GLWidget(QWidget *parent) : Tucano::QtTrackballWidget(parent)
{

}

GLWidget::~GLWidget()
{

}
void GLWidget::initialize()
{
    Tucano::QtTrackballWidget::initialize();
//    Tucano::QtTrackballWidget::openMesh("../../tucano-master/samples/models/toy.ply");
      Tucano::QtTrackballWidget::openMesh("urna/urna.ply");

    phong.setShadersDir("./effects/shaders/");
    phong.initialize();
}

void GLWidget::paintGL()
{
    makeCurrent();

    glClearColor(0.3, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);

    phong.render(mesh, camera, light_trackball);

    camera.render();
}
