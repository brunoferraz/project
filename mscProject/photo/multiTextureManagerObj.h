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
#include <mesh.hpp>
#include <utils/objimporter.hpp>
#include <utils/plyimporter.hpp>
#include <QGLWidget>
#include <texture.hpp>


struct RasterInfo{
//    std::string& operator<<(RasterInfo l){return l.label;}
    std::string filename;
    std::string label;
    PhotoCamera photoCamera;
    Tucano::Texture baseTexture;
};

class MultiTextureManagerObj
{
public:
    MultiTextureManagerObj();

    bool initializeFromMeshLab(QString path, QString photoPath = "");

    Eigen::Matrix4f *getProjectionMatrix();
    Eigen::Affine3f *getViewMatrix();
    Eigen::Matrix4f *getModelMatrix();
    Tucano::Texture *getBaseTexture();
    Tucano::Mesh    *getMesh();
    inline int getCountPhotos(){return rasterGroup.count();}

    void calibrateCamera(Tucano::Camera &c);

    void changePhotoReferenceTo(int n);
    inline void nextPhoto(){changePhotoReferenceTo(1);}
    inline void prevPhoto(){changePhotoReferenceTo(-1);}

private:
    Eigen::Matrix4f     modelMatrix;
    std::string         filename;
    std::string         label;
    QList<RasterInfo *> rasterGroup;
    Tucano::Mesh        mesh;
    int                 currentPhotoIndex;
    void openMesh(string filename);
};

#endif // PHOTOMESH_H
