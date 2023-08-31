//
// Created by fangl on 2023/8/31.
//

#ifndef GL_RENDERER_H
#define GL_RENDERER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Core>

#include "curve_model.h"


class GLRenderer : QOpenGLWidget
{
    Q_OBJECT
public:
    explicit GLRenderer(CurveModel *model, QWidget* parent = nullptr,
                        int width = 800, int height = 600);

    void updateCurve();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

// variables
private:
    QOpenGLFunctions_4_3_Core *core;

// private function
private:
    // setup
    void setupShaders();
    void setupBuffers();

    // draw
    void drawPoints();
    void drawCurves();

    CurveModel *m_model;
};


#endif //GL_RENDERER_H
