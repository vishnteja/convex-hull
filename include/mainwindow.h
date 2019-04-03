#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsLineItem>
#include <ConvexHull.h>
#include "graphicsscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    std::vector<QGraphicsLineItem> LineList;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_newPlot_clicked();

    void on_plotButton_clicked();

    void on_nextButton_clicked();

    void on_previousButton_clicked();

private:
    Ui::MainWindow *ui;
    ConvexHull hull;
    int counter;
    GraphicsScene * currScene;
    GraphicsScene * mainScene;
};

#endif // MAINWINDOW_H
