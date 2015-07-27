#include "photocamera.h"
#include <QDebug>
#include <QStringList>

PhotoCamera::PhotoCamera()
{

}

bool PhotoCamera::initializeFromMeshLab(QDomElement &element)
{
    QStringList attTemp;
    //Get Translation
    attTemp = element.attribute("TranslationVector").split(" ");
    for(int i = 0; i < attTemp.count(); i++){
        translationMatrix(i) = attTemp[i].toFloat();
    }

    //Get Center;
    attTemp = element.attribute("CenterPx").split(" ");
    centerPx << attTemp.at(0).toFloat(), attTemp.at(1).toFloat();


    //Get RotationMatrix;
    attTemp = element.attribute("RotationMatrix").split(" ");
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            rotationMatrix(i, j) = attTemp[i*4 + j].toFloat();
        }
    }

    //Get Viewport;
    attTemp = element.attribute("ViewportPx").split(" ");
    viewport << attTemp.at(0).toFloat(), attTemp.at(1).toFloat();

    //Lens Distortion;
    attTemp = element.attribute("LensDistortion").split(" ");
    distortion << attTemp.at(0).toFloat(), attTemp.at(1).toFloat();
    //std::cout << distortion.transpose() << std::endl;

    //PixelSize;
    attTemp = element.attribute("PixelSizeMm").split(" ");
    pixelSize << attTemp.at(0).toFloat(), attTemp.at(1).toFloat();
    //std::cout << pixelSize.transpose() << std::endl;

    //Focal
    focalLength = element.attribute("FocalMm").toFloat();

    buildExtrinsic();
    buildIntrinsic();

    return true;
}

void PhotoCamera::buildIntrinsic()
{
    Eigen::Matrix3f Mi;
    Mi << -focalLength*oneOverDx, 0, centerPx(0),
            0, -focalLength*oneOverDy, centerPx(1),
            0, 0, 1;
    intrinsicMatrix.topLeftCorner(3, 3) = Mi;
}

void PhotoCamera::buildExtrinsic()
{
    extrinsicMatrix = rotationMatrix*translationMatrix;
}

