#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include "graphicsscene.h"
#include <QDebug>
#include <bits/stdc++.h>
#include <QPointF>
#include <QList>
#include "ConvexHull.h"
#include <QGraphicsLineItem>

void traverset(vector<Point > vec){
    cout<<endl;
    for (auto i = vec.begin(); i != vec.end(); i++){
        cout << i->first << ", "<<i->second <<endl;
    }
    cout<<endl<<endl;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GraphicsScene * scene = new GraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    counter = 0;
    mainScene = scene;
    currScene = scene;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_newPlot_clicked()
{
    ui->graphicsView->setScene(mainScene);
    currScene = mainScene;
    qDebug() << Q_FUNC_INFO << ui->newPlot->text();
    ui->graphicsView->scene()->clear();
    GraphicsScene * scene = static_cast<GraphicsScene *>(ui->graphicsView->scene());
    scene->emptyPointList();
    counter = 0;
}

void MainWindow::on_plotButton_clicked()
{
    if(!ui->radioJarvis->isChecked() && !ui->radioGraham->isChecked() && !ui->radioUltimate->isChecked())
    {
        qDebug() << Q_FUNC_INFO << "No algorithm checked";
        return;
    }
    ui->graphicsView->setScene(mainScene);
    counter = 0;
//    QList<QGraphicsItem *> itemList = ui->graphicsView->scene()->items();
//    for(int i=0; i< itemList.size(); i++)
//    {
//         if(itemList.at(i)->type() == 6)
//         {
//             ui->graphicsView->scene()->removeItem(itemList.at(i));
//         }
//    }

    ui->graphicsView->scene()->clear();

    GraphicsScene * scene = static_cast<GraphicsScene *>(ui->graphicsView->scene());
    QList<QPointF> *pointList = scene->getList();
    std::vector<std::Point> points;
    for(int i=0; i<pointList->size(); i++)
    {
        points.push_back(std::Point(pointList->at(i).x(), pointList->at(i).y()));
        scene->paintPoint(pointList->at(i).x(), pointList->at(i).y(), 0);
    }

    hull.setInput(points);
//    for(int i=0; i<points.size(); i++)
//    {
//        qDebug() << Q_FUNC_INFO << points.at(i).first << "," << points.at(i).second;
//    }

    if(ui->radioJarvis->isChecked())
    {
       hull.setHistory(hull.computeHull("jarvis"));
    }
    else if(ui->radioGraham->isChecked())
    {
       hull.setHistory(hull.computeHull("graham"));
    }
    else if(ui->radioUltimate->isChecked())
    {
       hull.setHistory(hull.computeHull("kps"));
    }
      auto output = hull.getOutput();
//    qDebug() << Q_FUNC_INFO << "OUTPUT:";
//    for(int i=0; i<output.size(); i++)
//    {
//        qDebug() << Q_FUNC_INFO << output.at(i).first << "," << output.at(i).second;
//    }
    for(int i=0; i < output.size(); i++)
    {
        QGraphicsLineItem *LineItem = new QGraphicsLineItem(output.at(i).first, output.at(i).second,
                                      output.at((i+1)%output.size()).first, output.at((i+1)%output.size()).second);
        ui->graphicsView->scene()->addItem(LineItem);
       // qDebug() << Q_FUNC_INFO << LineItem->type();
    }

}


void MainWindow::on_nextButton_clicked()
{
    ui->graphicsView->scene()->clear();
    if(currScene != mainScene && currScene != nullptr)
    {
        qDebug() << Q_FUNC_INFO << "INSIDE POINTER";
        delete currScene;
        currScene = nullptr;
    }
    qDebug() << Q_FUNC_INFO << "OUTSIDE 1";
    GraphicsScene * temp_scene = new GraphicsScene();
    currScene = temp_scene;
    vector<State > temp = hull.getHistory();
    qDebug() << Q_FUNC_INFO << "OUTSIDE 2 " <<temp.size() ;
    vector<Point > bold_e = temp.at(counter).getBoldE();
    vector<Point > bold_p = temp.at(counter).getBoldP();
    vector<Point > norm_e = temp.at(counter).getNormalE();
    vector<Point > norm_p = temp.at(counter).getNormalP();
    qDebug() << Q_FUNC_INFO << "OUTSIDE 3 "<<norm_e.size();
    traverset(norm_e);
    for(int i=0;i< norm_p.size();i++)
    {
        currScene->paintPoint(norm_p.at(i).first, norm_p.at(i).second, 0);
    }
    qDebug() << Q_FUNC_INFO << "OUTSIDE 4";
    for(int i=0;i< bold_p.size();i++)
    {
        currScene->paintPoint(bold_p.at(i).first, bold_p.at(i).second, 1);
    }
    qDebug() << Q_FUNC_INFO << "OUTSIDE 5 "<<norm_e.size()<<" " <<( (int)norm_e.size()-1 > 0);
    for(int i=0;(i+1)<norm_e.size();i++)
    {
        currScene->paintEdge(norm_e.at(i).first, norm_e.at(i).second, norm_e.at((i+1)%norm_e.size()).first, norm_e.at((i+1)%norm_e.size()).second, 0);
    }

//    for(auto i = norm_e.begin(); i!=norm_e.end()-1; i++)
//    {
//        Point temp = *i;
//        Point tempp = *(i+1);
//        qDebug() << Q_FUNC_INFO << "OUTSIDE 5.5";
//        //currScene->paintEdge(norm_e.at(i).first, norm_e.at(i).second, norm_e.at((i+1)%norm_e.size()).first, norm_e.at((i+1)%norm_e.size()).second, 0);
//        currScene->paintEdge(i->first, i->second, (i+1).first, (i+1).second);
//    }
    qDebug() << Q_FUNC_INFO << "OUTSIDE 6";
    for(int i=0;(i+1)< bold_e.size();i++)
    {
        currScene->paintEdge(bold_e.at(i).first, bold_e.at(i).second, bold_e.at((i+1)%bold_e.size()).first, bold_e.at((i+1)%bold_e.size()).second, 1);
    }
    qDebug() << Q_FUNC_INFO << "OUTSIDE 7";
    ui->graphicsView->setScene(currScene);
    qDebug() << Q_FUNC_INFO << "OUTSIDE 8";
    counter = (counter+1)%(temp.size());
}

void MainWindow::on_previousButton_clicked()
{
    ui->graphicsView->scene()->clear();
    if(currScene != mainScene && currScene != nullptr)
    {
        qDebug() << Q_FUNC_INFO << "INSIDE POINTER";
        delete currScene;
        currScene = nullptr;
    }
    qDebug() << Q_FUNC_INFO << "OUTSIDE 1";
    GraphicsScene * temp_scene = new GraphicsScene();
    currScene = temp_scene;
    vector<State > temp = hull.getHistory();
    qDebug() << Q_FUNC_INFO << "OUTSIDE 2 " <<temp.size() ;
    vector<Point > bold_e = temp.at(counter).getBoldE();
    vector<Point > bold_p = temp.at(counter).getBoldP();
    vector<Point > norm_e = temp.at(counter).getNormalE();
    vector<Point > norm_p = temp.at(counter).getNormalP();
    qDebug() << Q_FUNC_INFO << "OUTSIDE 3 "<<norm_e.size();
    traverset(norm_e);
    for(int i=0;i< norm_p.size();i++)
    {
        currScene->paintPoint(norm_p.at(i).first, norm_p.at(i).second, 0);
    }
    qDebug() << Q_FUNC_INFO << "OUTSIDE 4";
    for(int i=0;i< bold_p.size();i++)
    {
        currScene->paintPoint(bold_p.at(i).first, bold_p.at(i).second, 1);
    }
    qDebug() << Q_FUNC_INFO << "OUTSIDE 5 "<<norm_e.size()<<" " <<( (int)norm_e.size()-1 > 0);
    for(int i=0;(i+1)<norm_e.size();i++)
    {
        currScene->paintEdge(norm_e.at(i).first, norm_e.at(i).second, norm_e.at((i+1)%norm_e.size()).first, norm_e.at((i+1)%norm_e.size()).second, 0);
    }

//    for(auto i = norm_e.begin(); i!=norm_e.end()-1; i++)
//    {
//        Point temp = *i;
//        Point tempp = *(i+1);
//        qDebug() << Q_FUNC_INFO << "OUTSIDE 5.5";
//        //currScene->paintEdge(norm_e.at(i).first, norm_e.at(i).second, norm_e.at((i+1)%norm_e.size()).first, norm_e.at((i+1)%norm_e.size()).second, 0);
//        currScene->paintEdge(i->first, i->second, (i+1).first, (i+1).second);
//    }
    qDebug() << Q_FUNC_INFO << "OUTSIDE 6";
    for(int i=0;(i+1)< bold_e.size();i++)
    {
        currScene->paintEdge(bold_e.at(i).first, bold_e.at(i).second, bold_e.at((i+1)%bold_e.size()).first, bold_e.at((i+1)%bold_e.size()).second, 1);
    }
    qDebug() << Q_FUNC_INFO << "OUTSIDE 7";
    ui->graphicsView->setScene(currScene);
    qDebug() << Q_FUNC_INFO << "OUTSIDE 8";
    if(counter != 0)
        counter = (counter-1)%(temp.size());
    else
        counter = temp.size()-1;
}
