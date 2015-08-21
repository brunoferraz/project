#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <util/util.h>
#include <QString>
#include <QtXml>
#include <photo/multiTextureManagerObj.h>
#include <QKeyEvent>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
protected:
    void keyReleaseEvent(QKeyEvent *ev);
};

#endif // MAINWINDOW_H
