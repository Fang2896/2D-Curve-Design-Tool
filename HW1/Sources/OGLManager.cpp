//
// Created by fangl on 2023/6/6.
//

#include "OGLManager.h"
#include "Points.h"

std::unique_ptr<Points> points;


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

    points->addPoint({normalX, normalY});
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

    // initialize Objects
    points = std::make_unique<Points>();
    points->init();

    // initialize shader program
    pointShader = std::make_unique<Shader>(this);
    pointShader->compile(":/Resources/Shaders/point.vert", ":/Resources/Shaders/point.frag");

    // TODO: 可不可以用MVP矩阵来操作？ 增加一个缩放功能？

}

void OGLManager::resizeGL(int w, int h) {
    core->glViewport(0, 0, w, h);
}

void OGLManager::paintGL() {
    core->glClear(GL_COLOR_BUFFER_BIT);

    // Point Draw
    pointShader->use();
    points->drawPoints();
    pointShader->release();
}

void OGLManager::clearCanvas() {
    points->clearData();
    update();
}





