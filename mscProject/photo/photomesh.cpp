#include "photomesh.h"
#include <sstream>


PhotoMesh::PhotoMesh()
{

}

bool PhotoMesh::initializeFromMeshLab(QString path)
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

    //get modelMatrix
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
        info->label         = rasterTree.at(i).toElement().attribute("label").toStdString();
        std::cout << info->label << std::endl;
        info->filename      = rasterTree.at(i).firstChild().nextSibling().toElement().attribute("fileName").toStdString();
        PhotoCamera cam;
        QDomElement camDom  = rasterTree.at(i).firstChildElement();
        cam.initializeFromMeshLab(camDom);
        info->photoCamera    = cam;
        rasterGroup.push_back(info);
        std::cout << "" << std::endl;
    }
    return true;
}

