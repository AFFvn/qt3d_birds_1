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
    //variables
    QGLSceneNode * m_vertexScene;
};

#endif // VERTEXVIEW_H
