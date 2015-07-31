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
    QString str = "urna/objs/urna.mlp";
    photoMesh.initializeFromMeshLab(str);

    Tucano::QtTrackballWidget::initialize();
//    Tucano::QtTrackballWidget::openMesh("../../tucano-master/samples/models/toy.ply");

    Tucano::QtTrackballWidget::openMesh("urna/urna.ply");

    string shaders_dir("./effects/shaders/");

    phong.setShadersDir(shaders_dir);
    phong.initialize();

    renderTexture.setShadersDir(shaders_dir);
    renderTexture.initialize();

    changeCamera(0);
}

void GLWidget::paintGL()
{
    makeCurrent();

    glClearColor(0.3, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);

    phong.render(mesh, calibrationCamera, light_trackball);

    Eigen::Vector2i viewport (this->width(), this->height());
    camera.render();
//    renderTexture.renderTexture(image_Texture, viewport);
}

void GLWidget::changeCamera(int c)
{
    int next = currentCamera + c;
    if(next >= photoMesh.rasterGroup.count()){
        next = 0;
    }else if(next < 0){
        next = photoMesh.rasterGroup.count()-1;
    }
    currentCamera = next;
    PhotoCamera &cam = photoMesh.rasterGroup.at(currentCamera)->photoCamera;
    RasterInfo *info = photoMesh.rasterGroup.at(currentCamera);
    mesh.setModelMatrix(Eigen::Affine3f::Identity());
    Eigen::Affine3f view = cam.extrinsicMatrix;
    calibrationCamera.setViewport(Eigen::Vector2f(this->size().width(), this->size().height()));
    calibrationCamera.setProjectionMatrix(cam.projectionMatrix);
    calibrationCamera.setViewMatrix(view);
    QString path = QString::fromStdString(info->filename);
    QImage img(path);
    QImage glImage = QGLWidget::convertToGLFormat(img);
    image_Texture.create(glImage.width(), glImage.height(), glImage.bits());

    update();
}
