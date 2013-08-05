#include <QtGui/QMouseEvent>
#include "gglgraph.h"
#include <GL/glu.h>

GglGraph::GglGraph(QWidget *parent) : QGLWidget(parent)
{
    scaleToFit = true;
    showGrid = true;
}

void GglGraph::initializeGL()
{
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0, 0, 0, 0);
}

void GglGraph::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, -h/2, h/2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GglGraph::paintGL()
{
    double scaleValue = 1;

    if(scaleToFit)
    {
        double max = 0, min = 0;

        foreach(double rVal, rSamples)
        {
            min = qMin(min, rVal);
            max = qMax(max, rVal);
        }

        foreach(double gVal, gSamples)
        {
            min = qMin(min, gVal);
            max = qMax(max, gVal);
        }

        foreach(double bVal, bSamples)
        {
            min = qMin(min, bVal);
            max = qMax(max, bVal);
        }

        scaleValue = qMax(max, -min);
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);


    if(showGrid)
    {
        glColor4f(0.3f, 0.3f, 0.3f, 0.8f);
        for(int hLine = 0; hLine < 9; hLine++)
        {
            glVertex2f(0, hLine/10.0*this->height()/2/scaleValue);
            glVertex2f(this->width(), hLine/10.0*this->height()/2/scaleValue);

            glVertex2f(0, -hLine/10.0*this->height()/2/scaleValue);
            glVertex2f(this->width(), -hLine/10.0*this->height()/2/scaleValue);


        }

        for(int vLine = 1; vLine < NUM_OF_SAMPLES/SAMPLES_PER_LINE; vLine++)
        {
            glVertex2f(this->width()*vLine/(NUM_OF_SAMPLES/SAMPLES_PER_LINE) , this->height()/2);
            glVertex2f(this->width()*vLine/(NUM_OF_SAMPLES/SAMPLES_PER_LINE) , -this->height()/2);
        }
    }

    glColor3f(1,0,0);
    for(int r = 0; r < rSamples.size()-1; r++)
    {
        glVertex2f( (GLfloat)r/NUM_OF_SAMPLES*this->width(), rSamples[r]*this->height()/2/scaleValue);
        glVertex2f( (GLfloat)(r+1)/NUM_OF_SAMPLES*this->width(), rSamples[r+1]*this->height()/2/scaleValue);
    }

    glColor3f(0,1,0);
    for(int g = 0; g < gSamples.size()-1; g++)
    {
        glVertex2f( (GLfloat)g/NUM_OF_SAMPLES*this->width(), gSamples[g]*this->height()/2/scaleValue);
        glVertex2f( (GLfloat)(g+1)/NUM_OF_SAMPLES*this->width(), gSamples[g+1]*this->height()/2/scaleValue);
    }

    glColor3f(0,0,1);
    for(int b = 0; b < rSamples.size()-1; b++)
    {
        glVertex2f( (GLfloat)b/NUM_OF_SAMPLES*this->width(), bSamples[b]*this->height()/2/scaleValue);
        glVertex2f( (GLfloat)(b+1)/NUM_OF_SAMPLES*this->width(), bSamples[b+1]*this->height()/2/scaleValue);
    }

    glEnd();

}


void GglGraph::insertSamplesR(const QVector<double> &samplesToInsert)
{
    if(rSamples.size()+samplesToInsert.size() > NUM_OF_SAMPLES)
    {
        rSamples.remove(0, (rSamples.size()+samplesToInsert.size())-NUM_OF_SAMPLES);
    }

    rSamples+=samplesToInsert;
}

void GglGraph::insertSamplesG(const QVector<double> &samplesToInsert)
{
    if(gSamples.size()+samplesToInsert.size() > NUM_OF_SAMPLES)
    {
        gSamples.remove(0, (gSamples.size()+samplesToInsert.size())-NUM_OF_SAMPLES);
    }

    gSamples+=samplesToInsert;
}

void GglGraph::insertSamplesB(const QVector<double> &samplesToInsert)
{
    if(bSamples.size()+samplesToInsert.size() > NUM_OF_SAMPLES)
    {
        bSamples.remove(0, (bSamples.size()+samplesToInsert.size())-NUM_OF_SAMPLES);
    }

    bSamples+=samplesToInsert;
}

void GglGraph::insertSamplesRGB(const QVector<double> &samplesToInsertR, const QVector<double> &samplesToInsertG, const QVector<double> &samplesToInsertB)
{
    insertSamplesR(samplesToInsertR);
    insertSamplesG(samplesToInsertG);
    insertSamplesB(samplesToInsertB);
}


