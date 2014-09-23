#include "vertexview.h"
#include "vertex.h"

#include "qglscenenode.h"
#include "qray3d.h"
#include "qplane3d.h"

#include "boost/multi_array.hpp"

#include <QMouseEvent>
#include <QDebug>
#include <QTime>


VertexView::VertexView(QWindow * parent)
    : QGLView(parent)
    , m_vertexScene(new QGLSceneNode)
{
    m_vertexScene->setParent(this);
    m_vertexScene->setPalette(QSharedPointer<QGLMaterialCollection>(new QGLMaterialCollection(this)));
    m_vertexScene->setEffect(QGL::LitMaterial);
    setTitle(QString("3d Birds Test"));
    dowork();
}

VertexView::~VertexView()
{}

Vertex * VertexView::addVertex()
{
    Vertex * vertex = new Vertex(m_vertexScene);
    vertex->setObjectName(QString("A Vertex"));
    connect(vertex, SIGNAL(updated()), this, SLOT(update()));
    return vertex;
}

void VertexView::paintGL(QGLPainter *painter)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_vertexScene->draw(painter);
}

void VertexView::initializeGL(QGLPainter *painter)
{
    painter->setClearColor(Qt::black);
    camera()->setEye(camera()->eye() + QVector3D(10.0f, 10.0f, 10.0f));
    glEnable(GL_BLEND);
}

void VertexView::mouseDoubleClickEvent(QMouseEvent *e)
{
    Vertex *vertex = addVertex();
    QVector3D pick = mapPoint(e->pos());

    QRay3D eyeline(camera()->eye(), (camera()->center() - camera()->eye()).normalized());
    QVector3D nearPlaneOrigin = eyeline.point(camera()->nearPlane());

    // from the near plane origin move up and across by the pick's XY to find the point
    // on the near plane
    QRay3D up(nearPlaneOrigin, camera()->upVector());
    QVector3D sideDir = QVector3D::crossProduct(camera()->upVector(), -eyeline.direction());
    QRay3D side(up.point(pick.y()), sideDir.normalized());
    QVector3D v = side.point(pick.x());

    // intersect the ray thru the picked point on the near plane with the floor
    QRay3D ray(camera()->eye(), v - camera()->eye());
    QPlane3D floorPlane(QVector3D(), QVector3D(0, 1, 0));
    QVector3D pointOnFloor = ray.point(floorPlane.intersection(ray));
    vertex->setPosition(pointOnFloor);
}

void VertexView::buildGrid()
{
    for (int i = 0 ; i < 10; i++)
    {
        for (int x = 0; x < 10; x++)
        {
            for (int y = 0; y < 10; y++)
            {
                Vertex * vertex = addVertex();
                vertex->setPosition(QVector3D(x, y, i));

            }
        }
    }
}

void VertexView::dowork()
{
    int dim = 50;
    int noofbird = 10000;
    QTime time = QTime::currentTime();
    unsigned long s = time.msec();
    srand(s);
    QVector < QVector < QVector< int > > > mainvec(dim,
                                                   QVector < QVector <int > > (dim,
                                                                               QVector < int > (dim, 0)));
    QVector < QVector < QVector< int > > > positionvec(dim,
                                                   QVector < QVector <int > > (dim,
                                                                               QVector < int > (dim, 0)));
    QVector < QVector < QVector< int > > > temp(dim,
                                                   QVector < QVector <int > > (dim,
                                                                               QVector < int > (dim, 0)));
    mainvec[dim/2][dim/2][dim/2] = noofbird;

    int done = 1;
    while (done != 0)
    {
        done = 0;
        for (int z = 0 ; z < dim; z++)
        {
            for (int y = 0 ; y < dim ; y++)
            {
                for (int x = 0 ; x < dim; x++)
                {
                    if ( mainvec[z][y][x] > 1){
                        done++;
                        int loop = mainvec[z][y][x];
                        for (int k = 0; k < loop; k++)
                        {               
                            int ran = rand() % 6;
                            if (ran == 0) {// move east
                                positionvec[z][y+1][x]++; 
                            }
                            else if (ran == 1) {
                                positionvec[z][y-1][x]++;
                            }
                            else if (ran == 2) {// move north
                                positionvec[z][y][x+1]++;
                            }
                            else if (ran == 3) { // move south
                                positionvec[z][y][x-1]++;
                            }
                            else if (ran == 4) { // move up
                                positionvec[z+1][y][x]++;
                            }
                            else if (ran == 5) { // move down
                                positionvec[z-1][y][x]++;
                            }
                        }
                    }
                    else
                    {
                        positionvec[z][y][x] += mainvec[z][y][x];
                    }
                }
            }
        }
        if (done > 0)
        {
            mainvec = positionvec;
            positionvec = temp;
        }

    }

    //checking result , printing vertices
    int count = 0;
    for (int i = 0 ; i < dim; i++)
    {
        for (int x = 0; x < dim; x++)
        {
            for (int y = 0; y < dim; y++)
            {
                if (mainvec[i][x][y] ==1) {
                Vertex * v = addVertex();
                v->setPosition(QVector3D(y,x,i));
                }
            }
        }
    }

}
