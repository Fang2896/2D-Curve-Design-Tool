//
// Created by fangl on 2023/6/6.
//

#include "OGLManager.h"


OGLManager::OGLManager(QWidget *parent, int width, int height)
    : QOpenGLWidget(parent)
{
    this->setGeometry(10, 10, width, height);
}

OGLManager::~OGLManager() {
    pointShader->release();
    gridShader->release();
    curveShader->release();
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
    polynomialInterpolateCurve->addInputPoints({spaceX, spaceY});
    gaussianInterpolateCurve->addInputPoints({spaceX, spaceY});
    polynomialRegressionCurve->addInputPoints({spaceX, spaceY});
    uniformParamCurve->addInputPoints({spaceX, spaceY});
    chordalParamCurve->addInputPoints({spaceX, spaceY});
    centrietalParamCurve->addInputPoints({spaceX, spaceY});

    qDebug() << "x: " << spaceX << "y: " << spaceY;

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

    polynomialInterpolateCurve = std::make_unique<PolynomialInterpolateCurve>();
    polynomialInterpolateCurve->init(1000, width(), height());

    gaussianInterpolateCurve = std::make_unique<RBFInterpolateCurve>(Kernel_Type::GAUSSIAN);    // sigma = 1
    gaussianInterpolateCurve->init(1000, width(), height());

    polynomialRegressionCurve = std::make_unique<PolynomialRegressionCurve>();
    polynomialRegressionCurve->init(1000, width(), height());

    uniformParamCurve = std::make_unique<UniformParamCurve>();
    uniformParamCurve->init(1000, width(), height());

    chordalParamCurve = std::make_unique<ChordalParamCurve>();
    chordalParamCurve->init(1000, width(), height());

    centrietalParamCurve = std::make_unique<CentrietalParamCurve>();
    centrietalParamCurve->init(1000, width(), height());

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
    polynomialInterpolateCurve->setWidgetSize(w, h);
    gaussianInterpolateCurve->setWidgetSize(w, h);
    polynomialRegressionCurve->setWidgetSize(w, h);
    uniformParamCurve->setWidgetSize(w, h);
    chordalParamCurve->setWidgetSize(w, h);
    centrietalParamCurve->setWidgetSize(w, h);

    update();
}

void OGLManager::paintGL() {
    core->glClear(GL_COLOR_BUFFER_BIT);

    updateGL();

    pointShader->use();
    points->drawPoints();

    gridShader->use();
    grid->drawGrid();

    if(isDrawPolyInterCurve) {
        curveShader->use().setColor("color" ,QColor(255, 0, 0));
        polynomialInterpolateCurve->drawCurve();
    }

    if(isDrawGaussianInterCurve) {
        curveShader->use().setColor("color" ,QColor(255, 255, 0));
        gaussianInterpolateCurve->drawCurve();
    }

    if(isDrawPolyRegressionCurve) {
        curveShader->use().setColor("color" ,QColor(0, 0, 255));
        polynomialRegressionCurve->drawCurve();
    }

    if(isDrawUniformParamCurve) {
        curveShader->use().setColor("color" ,QColor(255, 255, 0));  // yellow
        uniformParamCurve->drawCurve();
    }

    if(isDrawChordalParamCurve) {
        curveShader->use().setColor("color" ,QColor(128, 0, 128));  // purple
        chordalParamCurve->drawCurve();
    }

    if(isDrawCentrietalParamCurve) {
        curveShader->use().setColor("color" ,QColor(0, 255, 255));  // 青色
        centrietalParamCurve->drawCurve();
    }

}

void OGLManager::updateGL() {
    QMatrix4x4 projection, view;
    view.setToIdentity();
    projection.ortho(-(float)width() / 2.0f, (float)width() / 2.0f,
                     -(float)height() / 2.0f, (float)height() / 2.0f, -1.0f, 1.0f);

    pointShader->use().setMatrix4f("view", view);
    pointShader->use().setMatrix4f("projection", projection);

    gridShader->use().setMatrix4f("view", view);
    gridShader->use().setMatrix4f("projection", projection);

    curveShader->use().setMatrix4f("view", view);
    curveShader->use().setMatrix4f("projection", projection);

}

void OGLManager::clearCanvas() {
    points->clearData();
    polynomialInterpolateCurve->clearData();
    gaussianInterpolateCurve->clearData();
    polynomialRegressionCurve->clearData();
    uniformParamCurve->clearData();
    chordalParamCurve->clearData();
    centrietalParamCurve->clearData();

    update();
}

void OGLManager::resolutionChange(int res) {
    polynomialInterpolateCurve->setResolution(res);
    gaussianInterpolateCurve->setResolution(res);
    polynomialRegressionCurve->setResolution(res);
    uniformParamCurve->setResolution(res);
    chordalParamCurve->setResolution(res);
    centrietalParamCurve->setResolution(res);

    update();
}

void OGLManager::drawPolyInterCurve(bool isDraw) {
    this->isDrawPolyInterCurve = isDraw;
    update();
}

void OGLManager::drawGaussianInterCurve(bool isDraw) {
    this->isDrawGaussianInterCurve = isDraw;
    update();
}

void OGLManager::setGaussianInterSigma(float sigma) {
    gaussianInterpolateCurve->setSigma(sigma);
    update();
}

void OGLManager::drawPolyRegreCurve(bool isDraw) {
    isDrawPolyRegressionCurve = isDraw;
    update();
}

void OGLManager::setPolyRegreOrder(int order) {
    polynomialRegressionCurve->setOrder(order);
    update();
}

void OGLManager::setPolyRegreLambda(float lambda) {
    polynomialRegressionCurve->setLambda(lambda);
    update();
}

// params:
void OGLManager::drawUniformParamCurve(bool isDraw) {
    isDrawUniformParamCurve = isDraw;
    update();
}

void OGLManager::drawChordalParamCurve(bool isDraw) {
    isDrawChordalParamCurve = isDraw;
    update();
}

void OGLManager::drawCentrietalParamCurve(bool isDraw) {
    isDrawCentrietalParamCurve = isDraw;
    update();
}



