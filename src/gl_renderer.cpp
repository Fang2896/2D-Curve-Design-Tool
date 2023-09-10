//
// Created by fangl on 2023/8/31.
//

#include "gl_renderer.h"


GLRenderer::GLRenderer(CurveModel &model, QWidget* parent, int width, int height)
    : QOpenGLWidget(parent), m_model(model)
{
    this->setGeometry(10, 10, width, height);
}

void GLRenderer::initializeGL() {
    core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    core->glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    core->glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    initBuffers();
    initShaders();

    QMatrix4x4 model;
    model.setToIdentity();
    pointShader->use().setMatrix4f("model", model);
}

void GLRenderer::resizeGL(int w, int h) {
    core->glViewport(0, 0, w, h);

    // modify drawing curves' size ...


}

void GLRenderer::paintGL() {
    core->glClear(GL_COLOR_BUFFER_BIT);

    updateViewProjectMatrix();

    // draw
    pointShader->use();
    core->glBindVertexArray(pointsVAO);
    core->glDrawArrays(GL_POINTS, 0, m_model.getPointsSize());
    core->glBindVertexArray(0);

    // others ...
}

void GLRenderer::updatePointsBuffer() {
    core->glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
    core->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D) * m_model.getPointsSize(),
                       m_model.getPointsData(), GL_STATIC_DRAW);
    core->glBindBuffer(GL_ARRAY_BUFFER, 0);

    core->glBindBuffer(GL_ARRAY_BUFFER, pointsColorVBO);
    core->glBufferData(GL_ARRAY_BUFFER, sizeof(QColor) * m_model.getPointsSize(),
                       m_model.getColorsData(), GL_STATIC_DRAW);
    core->glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLRenderer::updateCurveBuffer() {
    // 更新曲线的buffer等。重新计算数据

}

void GLRenderer::updateCanvas() {
    updatePointsBuffer();
    updateCurveBuffer();
    update();
}


// other functions
void GLRenderer::setCurrentCurveType(CurveType type) {
    m_currentCurveType = type;
    // update something...
}

void GLRenderer::initBuffers() {
    /*********** VBO **********/
    core->glGenBuffers(1, &pointsVBO);
    core->glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
    core->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D) * m_model.getPointsSize(),
                       m_model.getPointsData(), GL_STATIC_DRAW);
    core->glBindBuffer(GL_ARRAY_BUFFER, 0);

    core->glGenBuffers(1, &pointsColorVBO);
    core->glBindBuffer(GL_ARRAY_BUFFER, pointsColorVBO);
    core->glBufferData(GL_ARRAY_BUFFER, sizeof(QColor) * m_model.getPointsSize(),
                       m_model.getColorsData(), GL_STATIC_DRAW);
    core->glBindBuffer(GL_ARRAY_BUFFER, 0);

    /*********** VAO **********/
    core->glGenVertexArrays(1, &pointsVAO);
    core->glBindVertexArray(pointsVAO);

    core->glEnableVertexAttribArray(0);
    core->glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
    core->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
                                2 * sizeof(float), (void*) nullptr);
    core->glBindVertexArray(0);

    core->glGenVertexArrays(1, &pointsColorVAO);
    core->glBindVertexArray(pointsColorVAO);

    core->glEnableVertexAttribArray(1);
    core->glBindBuffer(GL_ARRAY_BUFFER, pointsColorVBO);
    core->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                                3 * sizeof(float), (void*) nullptr);
    core->glBindVertexArray(0);
}

void GLRenderer::initShaders() {
    pointShader = std::make_unique<Shader>(this);
    pointShader->compile(":/resources/shaders/point.vert",
                         ":/resources/shaders/point.frag");

    // other shaders...

}

void GLRenderer::updateViewProjectMatrix() {
    // 这里感觉可以加鼠标滚轮来实时更新显示大小

    QMatrix4x4 projection, view;
    view.setToIdentity();
    // 这个就等于是在三维了
    projection.ortho(-(float)width() / 2.0f, (float)width() / 2.0f,
                     -(float)height() / 2.0f, (float)height() / 2.0f, -1.0f, 1.0f);

    pointShader->use().setMatrix4f("view", view);
    pointShader->use().setMatrix4f("projection", projection);

    // other curves...
}

// control functions:
void GLRenderer::mouseMoveEvent(QMouseEvent *event) {

}

void GLRenderer::mousePressEvent(QMouseEvent *event) {
    auto mouseX = (float)event->x();
    auto mouseY = (float)event->y();
    auto spaceX = mouseX - (float)width() / 2.0f;
    auto spaceY = (float)height() / 2.0f - mouseY;

    // Convert mouse position to OpenGL coordinates
    if(event->modifiers() & Qt::ControlModifier && event->button() == Qt::LeftButton) {
        // qDebug() << "Current Data: " << m_model.getPointsData();
        m_model.addPoint({spaceX, spaceY});
    } else if(event->button() == Qt::LeftButton) {
        selectedPointIndex = m_model.findNearestPoint({spaceX, spaceY});
        if(selectedPointIndex != -1) {
            m_model.setPointColor(selectedPointIndex, Qt::red);
        }
    }

    updateCanvas();
}

void GLRenderer::mouseReleaseEvent(QMouseEvent *event) {

}

