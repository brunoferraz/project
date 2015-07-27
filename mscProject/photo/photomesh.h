#ifndef PHOTOMESH_H
#define PHOTOMESH_H
#include <Eigen/Eigen>
#include <photo/photocamera.h>
#include <QList>
#include <QString>
#include <QFile>
#include <QIODevice>
#include <QDomElement>
#include <QDomDocument>
#include <QDebug>
#include <util/util.h>

struct RasterInfo{
//    std::string& operator<<(RasterInfo l){return l.label;}
    std::string filename;
    std::string label;
    PhotoCamera photoCamera;
};

class PhotoMesh
{
public:
    PhotoMesh();
    Eigen::Matrix4f     modelMatrix;
    std::string         filename;
    std::string         label;
    QList<RasterInfo *>   rasterGroup;

    bool initializeFromMeshLab(QString path);
};

#endif // PHOTOMESH_H
