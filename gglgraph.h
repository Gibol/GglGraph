#ifndef _GGLGRAPH_H
#define _GGLGRAPH_H

#define NUM_OF_SAMPLES 2048
#define SAMPLES_PER_LINE 100

#include <QtOpenGL/QGLWidget>

class GglGraph : public QGLWidget {

    Q_OBJECT

public:
    GglGraph(QWidget *parent = NULL);
    bool scaleToFit;
    bool showGrid;
    void insertSamplesR(const QVector<double> &samplesToInsert);
    void insertSamplesG(const QVector<double> &samplesToInsert);
    void insertSamplesB(const QVector<double> &samplesToInsert);
    void insertSamplesRGB(const QVector<double> &samplesToInsertR, const QVector<double> &samplesToInsertG, const QVector<double> &samplesToInsertB);


protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    QVector<double> rSamples;
    QVector<double> gSamples;
    QVector<double> bSamples;

};

#endif  /* _GGLGRAPH_H */
