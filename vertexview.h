#ifndef VERTEXVIEW_H
#define VERTEXVIEW_H

#include "qglview.h"



class QGLSceneNode;

class Vertex;

class VertexView : public QGLView
{
public:
    VertexView(QWindow * parent = 0);
    ~VertexView();

protected:
    void initializeGL(QGLPainter *painter);
    void paintGL(QGLPainter *painter);
    void mouseDoubleClickEvent(QMouseEvent *e);

private:
    Vertex * addVertex();
    void buildGrid();
    void dowork();
    void dowork2();
    void async_get_next_v(int z, int y, int x);
    //variables
    QGLSceneNode * m_vertexScene;

    QVector < QVector < QVector< int > > > positions;
};

#endif // VERTEXVIEW_H
