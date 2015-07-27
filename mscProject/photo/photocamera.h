#ifndef PHOTOCAMERA_H
#define PHOTOCAMERA_H

#include <camera.hpp>
#include <QDomElement>
#include <QDomNode>

class PhotoCamera : public Tucano::Camera
{
public:
    PhotoCamera();
    Eigen::Matrix4f intrinsicMatrix;
    Eigen::Matrix4f extrinsicMatrix;
    Eigen::Vector4f translationMatrix;
    Eigen::Matrix4f rotationMatrix;
    Eigen::Vector2f centerPx;
    Eigen::Vector2f viewport;
    Eigen::Vector2f distortion;
    Eigen::Vector2f pixelSize;
    float focalLength;
    float oneOverDx;
    float oneOverDy;

    bool initializeFromMeshLab(QDomElement& element);
    void buildIntrinsic();
    void buildExtrinsic();
};

#endif // PHOTOCAMERA_H
