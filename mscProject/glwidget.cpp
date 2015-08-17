#include "glwidget.h"
GLWidget::GLWidget(QWidget *parent) : Tucano::QtTrackballWidget(parent)
{
    currentCamera = 0;
}

GLWidget::~GLWidget()
{

}
void GLWidget::initialize()
{
    glEnable (GL_BLEND);

    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    QString str = "urna/objs/urna.mlp";
    photoMesh.initializeFromMeshLab(str, QString("./urna/fotos/"));

    Tucano::QtTrackballWidget::initialize();
//    Tucano::QtTrackballWidget::openMesh("../../tucano-master/samples/models/toy.ply");

//    Tucano::QtTrackballWidget::openMesh("urna/urna.ply");

    string shaders_dir("./effects/shaders/");

    phong.setShadersDir(shaders_dir);
    phong.initialize();

    renderTexture.setShadersDir(shaders_dir);
    renderTexture.initialize();

//    changeCamera(0);
    calibrationCamera.setViewport(Eigen::Vector2f(this->size().width(), this->size().height()));
    photoMesh.calibrateCamera(calibrationCamera);
}

void GLWidget::paintGL()
{
    makeCurrent();

    glClearColor(0.3, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    Eigen::Vector2i viewport (this->width(), this->height());
    camera.render();

    glEnable(GL_DEPTH_TEST);
    phong.render(photoMesh.mesh, calibrationCamera, light_trackball);

    glDisable(GL_DEPTH_TEST);
    renderTexture.renderTexture(*photoMesh.getBaseTexture(), viewport);
}
