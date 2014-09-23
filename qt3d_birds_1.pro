TARGET = qt3d_birds_1
TEMPLATE = app
QT       += 3d

SOURCES += main.cpp\
    vertex.cpp \
    vertexview.cpp

HEADERS  += \
    vertex.h \
    vertexview.h

INCLUDEPATH += "/usr/local/Cellar/boost/1.55.0_2/include"
