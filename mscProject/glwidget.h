#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/glew.h>

#include <QWidget>
#include <phongshader.hpp>
#include <utils/qttrackballwidget.hpp>


class GLWidget : public Tucano::QtTrackballWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent);
    ~GLWidget();
    void initialize();
    void paintGL();

signals:

public slots:
};

#endif // GLWIDGET_H
