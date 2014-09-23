#ifndef VERTEX_H
#define VERTEX_H

#include "qglscenenode.h"

class Vertex : public QGLSceneNode
{
    Q_OBJECT

public:
    explicit Vertex(QObject * parent = 0);
    ~Vertex();

signals:

public slots:
private:
    static QGLSceneNode * vertexObject();

    QGLTexture2D *m_texture;
};

#endif // VERTEX_H
