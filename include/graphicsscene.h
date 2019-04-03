#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QList>

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicsScene(QObject *parent = nullptr);
    //virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent);
    //virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent);
    QList <QPointF>* getList();
    void emptyPointList();
    void paintPoint(long long int x, long long int y, int color);
    void paintEdge(long long int x1, long long int y1, long long int x2, long long int y2, int color);
signals:

public slots:

private:
    QList <QPointF> m_points;
};

#endif // GRAPHICSSCENE_H
