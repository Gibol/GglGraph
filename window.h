#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "gglgraph.h"


class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window();

private slots:
    void addRandoms();

private:
    GglGraph *openGL;

};


#endif
