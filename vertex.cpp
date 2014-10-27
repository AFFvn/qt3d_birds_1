#include "vertex.h"

#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>
#include <QImage>
#include <QPainter>
#include <QSize>

#ifndef QT_NO_DEBUG
#include <QThread>
#include <QCoreApplication>
#endif

#include "qglbuilder.h"
#include "qglsphere.h"
#include "qglmaterial.h"
#include "qgltexture2d.h"
#include "qgraphicsscale3d.h"
#include "qgraphicsrotation3d.h"
#include "qglcube.h"

Vertex::Vertex(QObject *parent)
    : QGLSceneNode(parent)
    , m_texture(0)
{
    addNode(vertexObject());
}

Vertex::~Vertex()
{
}

QGLSceneNode * Vertex::vertexObject()
{
#ifndef QT_NO_DEBUG
    // NOT THREADSAFE, NOT RE-ENTRANT
    Q_ASSERT(QThread::currentThread() == qApp->thread());
#endif
    static QGLSceneNode *v = 0;
    if (!v)
    {
        QGLBuilder build;
      //  build << QGLSphere(0.7f);
        build << QGLCube(1);
        v = build.finalizedSceneNode();
        v->setObjectName("Vertex Component");
        QGraphicsRotation3D *rot = new QGraphicsRotation3D(v);
        rot->setAxis(QVector3D(1, 0, 0));
        rot->setAngle(-90.0f);
        v->addTransform(rot);
        v->setY(-v->boundingBox().minimum().y());

    }
    return v;
}
