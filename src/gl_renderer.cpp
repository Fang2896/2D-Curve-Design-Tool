//
// Created by fangl on 2023/8/31.
//

#include "gl_renderer.h"


GLRenderer::GLRenderer(CurveModel *model, QWidget* parent, int width, int height)
    : QOpenGLWidget(parent), m_model(model)
{
    this->setGeometry(10, 10, width, height);
}

void GLRenderer::initializeGL() {
    core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    core->glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    core->glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);



}

void GLRenderer::resizeGL(int w, int h) {
    core->glViewport(0, 0, w, h);
}

void GLRenderer::paintGL() {
    core->glClear(GL_COLOR_BUFFER_BIT);
}






