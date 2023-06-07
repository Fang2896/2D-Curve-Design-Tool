//
// Created by fangl on 2023/6/6.
//

#include "OGLManager.h"


OGLManager::OGLManager(QWidget *parent, int width, int height)
    : QOpenGLWidget(parent)
{
    this->setGeometry(10, 10, width, height);
}


/***** Input Functions *****/
void OGLManager::mouseMoveEvent(QMouseEvent *event) {

}

void OGLManager::mousePressEvent(QMouseEvent *event) {
    // Convert the mouse position to OpenGL coordinates
    auto spaceX = static_cast<float >(event->x()) * 2.0f - (float)width();
    auto spaceY = (float)height() - static_cast<float>(event->y()) * 2.0f;

    auto normalX = spaceX / (float)width();
    auto normalY = spaceY / (float)height();

    points.push_back({normalX, normalY});

    // Update VBO
    pointVAO.bind();
    pointVBO.bind();
    pointVBO.allocate(points.data(), points.size() * sizeof(QVector2D));
    pointVAO.release();

    qDebug() << "x: " << spaceX << "y: " << spaceY << Qt::endl;

    update();
}

void OGLManager::mouseReleaseEvent(QMouseEvent *event) {

}


/***** GL Functions *****/
void OGLManager::initializeGL() {
    core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
    core->glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    core->glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    // initialize shader program
    bool success;
    pointShaderProgram = new QOpenGLShaderProgram(this);
    pointShaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Resources/Shaders/point.vert");
    pointShaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment,":/Resources/Shaders/point.frag");
    success = pointShaderProgram->link();
    if(!success) qDebug() << "Point Shader Link Error!" << Qt::endl;

    // initialize VAO / VBO
    pointVAO.create();
    pointVAO.bind();
    pointVBO.create();
    pointVBO.bind();
    pointShaderProgram->enableAttributeArray(0);
    pointShaderProgram->setAttributeBuffer(0, GL_FLOAT, 0, 2);
    pointVAO.release();

}

void OGLManager::resizeGL(int w, int h) {
    core->glViewport(0, 0, w, h);
}

void OGLManager::paintGL() {
    core->glClear(GL_COLOR_BUFFER_BIT);

    // Point Draw
    pointShaderProgram->bind();
    pointVAO.bind();
    core->glDrawArrays(GL_POINTS, 0, points.size());
    pointVAO.release();
    pointShaderProgram->release();
}

void OGLManager::clearCanvas() {
    points.clear();
    update();
}





