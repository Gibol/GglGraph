
#include <QtGui>
#include <QDebug>

#include "window.h"

Window::Window() : QMainWindow()
{
    this->hide();
    openGL = new GglGraph();
    openGL->setWindowTitle("GglGraph");

    openGL->show();

    QTime time = QTime::currentTime();
        qsrand((uint)time.msec());


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(addRandoms()));

    timer->start(20);
}


void Window::addRandoms()
{
    static int refreshPerSecond = 0;
    static int currentSecond = QTime::currentTime().second();

    QVector<double> newVals;
    for(int i = 0; i < 50; i++)
    {
        double randval = ((qrand()%2000)-1000)/4000.0;
        newVals.append(randval);
    }

    openGL->insertSamplesR(newVals);
     newVals.resize(0);

    for(int i = 0; i < 50; i++)
    {
        double randval = ((qrand()%500)-250)/1000.0 + (qrand()%10/20.0 -0.25) + 0.2;
        newVals.append(randval);
    }

    openGL->insertSamplesG(newVals);
    newVals.resize(0);

    for(int i = 0; i < 50; i++)
    {
        double randval = ((qrand()%1000)-500)/2000.0 - (qrand()%20/100.0 - 0.05) - 0.2;;
        newVals.append(randval);
    }

    openGL->insertSamplesB(newVals);

    openGL->repaint();
    refreshPerSecond++;

    if(currentSecond != QTime::currentTime().second())
    {
        currentSecond = QTime::currentTime().second();
        qDebug()<<"FPS: "<<refreshPerSecond;
        refreshPerSecond =0;
    }
}
