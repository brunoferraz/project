#include "glwidget.h"
GLWidget::GLWidget(QWidget *parent) : Tucano::QtTrackballWidget(parent)
{

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

    phong.setShadersDir("./effects/shaders/");
    phong.initialize();
    PhotoCamera &cam = photoMesh.rasterGroup.at(0)->photoCamera;
    //    camera.initOpenGLMatrices();
    float scale = mesh.getScale();
    cout << "scale: " << scale << endl;
    mesh.setModelMatrix(Eigen::Affine3f::Identity());
    Eigen::Affine3f view = cam.extrinsicMatrix;
    calibrationCamera.setViewport(Eigen::Vector2f(this->size().width(), this->size().height()));

    camera.setProjectionMatrix(cam.projectionMatrix);
    camera.setViewMatrix(view);
    //camera.applyScaleToViewMatrix(mesh.getScale());


    calibrationCamera.setProjectionMatrix(cam.projectionMatrix);
    cout << "projection: " << endl << *(calibrationCamera.projectionMatrix()) << endl;
//    view.matrix() = view.matrix() * scale;
//    view.matrix()(3,3) = 1;
    scale = 1;
//    mesh.modelMatrix()->matrix() *= ((1 -scale) + 1);
//    view.scale(scale);
//    view.translation() *= scale;
//    view.matrix()(3,3) = 1;
    cout << "view scale: " << endl << view.matrix() << endl;
    calibrationCamera.setViewMatrix(view);
    //calibrationCamera.translate(Eigen::Vector3f(0, 0, 200));

    //mesh.modelMatrix().matrix() = Eigen::Matrix4f::Identity();
}

void GLWidget::paintGL()
{
    makeCurrent();

    glClearColor(0.3, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);

    phong.render(mesh, calibrationCamera, light_trackball);
    camera.render();
//    std::cout << camera.getProjectionMatrix() << std::endl;
}
