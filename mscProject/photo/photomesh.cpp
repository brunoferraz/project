#include "photomesh.h"
#include <sstream>


PhotoMesh::PhotoMesh()
{
    PhotoMesh::currentPhotoIndex = 0;
}

bool PhotoMesh::initializeFromMeshLab(QString path, QString photoPath)
{
    QDomDocument doc;
    QFile file(path);
    qDebug() << file.exists();
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "failed to open";
        return -1;
    }else{
        if(!doc.setContent(&file))
        {
            qDebug() << "failed to load document";
            return -1;
        }
        file.close();
    }
    QDomElement root = doc.firstChildElement();
    QDomNodeList meshTree = root.elementsByTagName("MeshGroup");
    QDomNodeList rasterTree = root.elementsByTagName("MLRaster");
    //QNodeList percorre por indice porem vc precisa saber o nome da tag
    filename = root.firstChildElement().firstChildElement().attribute("filename").toStdString();
    label    = root.firstChildElement().firstChildElement().attribute("label").toStdString();

    openMesh("./urna/objs/"+filename);

    std::stringstream m(root.firstChildElement().firstChildElement().firstChildElement().text().toStdString());
    int i = 0;
    float a, b, c, d;
    while(m >> a >> b >> c >> d){
        Eigen::Vector4f v;
        v << a, b, c, d;
        modelMatrix.row(i) = v.transpose();
        i++;
    }
    //get raster info
    int total = rasterTree.count();
    for(int i =0; i < total; i++){
        RasterInfo *info = new RasterInfo();
        info->label = rasterTree.at(i).toElement().attribute("label").toStdString();
        if(photoPath==""){
            //use defautl path from mesh lab file
            info->filename = rasterTree.at(i).firstChild().nextSibling().toElement().attribute("fileName").toStdString();
        }else{
            //set your own path
            info->filename = photoPath.toStdString() + info->label;
        }
        QImage img(QString::fromStdString(info->filename));
        QImage glImage = QGLWidget::convertToGLFormat(img);
        info->baseTexture.create(glImage.width(), glImage.height(), glImage.bits());

        PhotoCamera cam;
        QDomElement camDom  = rasterTree.at(i).firstChildElement();
        cam.initializeFromMeshLab(camDom);
        info->photoCamera    = cam;
        rasterGroup.push_back(info);
    }

    return true;
}
Eigen::Matrix4f *PhotoMesh::getProjectionMatrix()
{
    return &rasterGroup.at(currentPhotoIndex)->photoCamera.projectionMatrix;
}
Eigen::Affine3f *PhotoMesh::getViewMatrix()
{
    return &rasterGroup.at(currentPhotoIndex)->photoCamera.extrinsicMatrix;
}
Eigen::Matrix4f *PhotoMesh::getModelMatrix()
{
    return &modelMatrix;
}

Tucano::Texture *PhotoMesh::getBaseTexture()
{
    return &rasterGroup.at(currentPhotoIndex)->baseTexture;
}

void PhotoMesh::calibrateCamera(Tucano::Camera &c)
{
    //Receive the camera and calibrate it using info from de current raster image
    PhotoCamera &cam = rasterGroup.at(currentPhotoIndex)->photoCamera;
    RasterInfo *info = rasterGroup.at(currentPhotoIndex);

    Eigen::Affine3f view = cam.extrinsicMatrix;
    c.setProjectionMatrix(cam.projectionMatrix);
    c.setViewMatrix(view);
}

void PhotoMesh::changePhotoReferenceTo(int n)
{
    int next = currentPhotoIndex + n;
    if(next >= rasterGroup.count()) next = 0;
    if(next < 0) next = rasterGroup.count()-1;
    currentPhotoIndex = next;
}

void PhotoMesh::openMesh(string filename)
{
    QString str (filename.c_str());
    QStringList strlist = str.split(".");
    QString extension = strlist[strlist.size()-1];

    if (extension.compare("ply") != 0 && extension.compare("obj") != 0)
    {
        cerr << "file format [" << extension.toStdString() << "] not supported" << endl;
        return;
    }

    mesh.reset();

    if (extension.compare("ply") == 0)
    {
        Tucano::MeshImporter::loadPlyFile(&mesh, filename);
    }
    if (extension.compare("obj") == 0)
    {
        Tucano::MeshImporter::loadObjFile(&mesh, filename);
    }
}
