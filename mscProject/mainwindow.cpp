#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->initialize();

    PhotoMesh photoMesh;
    QString str = "urna/objs/urna.mlp";
    photoMesh.initializeFromMeshLab(str);
}

MainWindow::~MainWindow()
{
    delete ui;
}
