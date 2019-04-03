#ifndef MYSCENEVIEW_H
#define MYSCENEVIEW_H
#include <QGraphicsView>
#include <QGraphicsScene>

class MySceneView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MySceneView(QWidget *parent = NULL);

signals:

public slots:
    void mousePressEvent(QMouseEvent * e);
    // void mouseReleaseEvent(QMouseEvent * e);
    // void mouseDoubleClickEvent(QMouseEvent * e);
    // void mouseMoveEvent(QMouseEvent * e);
private:
    QGraphicsScene * scene;
};

#endif // MYSCENEVIEW_H
