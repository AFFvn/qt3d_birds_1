
#include <QGuiApplication>

#include "vertexview.h"

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    VertexView view;
    view.show();
    return a.exec();
}
