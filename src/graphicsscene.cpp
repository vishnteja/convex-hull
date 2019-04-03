#include "graphicsscene.h"
#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include "qmath.h"
#include <iostream>

GraphicsScene::GraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{
    this->setBackgroundBrush(Qt::white);
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    qDebug() << Q_FUNC_INFO << mouseEvent->scenePos();
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent * me)
{
    qDebug() << Q_FUNC_INFO << me->scenePos() << " "<< m_points.size();
    int radius = 5;
    QGraphicsEllipseItem * ellipse = this->addEllipse(me->scenePos().x() - radius, me->scenePos().y() - radius, radius*2, radius*2);

    ellipse->setBrush(Qt::blue);
    m_points.append(me->scenePos());

    QGraphicsScene::mouseReleaseEvent(me);
}

QList <QPointF>* GraphicsScene::getList()
{
    return &m_points;
}

void GraphicsScene::emptyPointList()
{
    m_points.clear();
}

void GraphicsScene::paintPoint(long long int x, long long int y, int color)
{
    QGraphicsEllipseItem * ellipse = this->addEllipse(x - 5, y - 5, 10, 10);
    if(color == 0)
    {
        ellipse->setBrush(Qt::blue);
    }
    else
    {
        ellipse->setBrush(Qt::red);
    }
}

void GraphicsScene::paintEdge(long long int x1, long long int y1, long long int x2, long long int y2, int color)
{
    qDebug() << Q_FUNC_INFO << "PAINTEDGE";
    QGraphicsLineItem * line = this->addLine(x1, y1, x2, y2);
    if(color == 1)
    {
        line->setPen(QPen(QColor(Qt::magenta)));
    }
}
