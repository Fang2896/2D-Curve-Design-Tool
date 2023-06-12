//
// Created by fangl on 2023/6/6.
//

#include "OGLManager.h"
#include "Points.h"
#include "Grid.h"
#include "Curve.h"

std::unique_ptr<Points> points;
std::unique_ptr<Grid> grid;
std::unique_ptr<PolynomialFittingCurve> polyfitCurve;


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
    auto mouseX = (float)event->x();
    auto mouseY = (float)event->y();
    auto spaceX = mouseX - (float)width() / 2.0f;
    auto spaceY = (float)height() / 2.0f - mouseY;

    points->addPoint({spaceX, spaceY});
    polyfitCurve->addInputPoints({spaceX, spaceY});
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

    grid = std::make_unique<Grid>(width(), height());
    grid->init();

    polyfitCurve = std::make_unique<PolynomialFittingCurve>();
    polyfitCurve->init(40, width(), height());

    // initialize shader program
    pointShader = std::make_unique<Shader>(this);
    pointShader->compile(":/Resources/Shaders/point.vert",
                         ":/Resources/Shaders/point.frag");

    gridShader = std::make_unique<Shader>(this);
    gridShader->compile(":/Resources/Shaders/grid.vert",
                        ":/Resources/Shaders/grid.frag");

    curveShader = std::make_unique<Shader>(this);
    curveShader->compile(":/Resources/Shaders/curve.vert",
                        ":/Resources/Shaders/curve.frag");

    QMatrix4x4 model;
    model.setToIdentity();
    pointShader->use().setMatrix4f("model", model);
    gridShader->use().setMatrix4f("model", model);
    curveShader->use().setMatrix4f("model", model);

}

void OGLManager::resizeGL(int w, int h) {
    core->glViewport(0, 0, w, h);
}

void OGLManager::paintGL() {
    core->glClear(GL_COLOR_BUFFER_BIT);

    QMatrix4x4 projection, view;
    view.setToIdentity();
    projection.ortho(-400.0f, 400.0f, -200.0f, 200.0f, -1.0f, 1.0f);

    // Point Draw
    pointShader->use().setMatrix4f("view", view);
    pointShader->use().setMatrix4f("projection", projection);
    points->drawPoints();
    pointShader->release();

    // Grid Draw
    gridShader->use().setMatrix4f("view", view);
    gridShader->use().setMatrix4f("projection", projection);
    grid->drawGrid();
    gridShader->release();

    // Curve Draw
    curveShader->use().setMatrix4f("view", view);
    curveShader->use().setMatrix4f("projection", projection);
    polyfitCurve->drawCurve();
    curveShader->release();

}

void OGLManager::clearCanvas() {
    points->clearData();
    polyfitCurve->clearData();
    update();
}

