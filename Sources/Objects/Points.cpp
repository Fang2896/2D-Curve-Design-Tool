//
// Created by fangl on 2023/6/7.
//

#include "Headers/Points.h"

Points::Points() {
    pointsVAO = 0;
    pointsVBO = 0;
    core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
}

Points::~Points() {
    core->glDeleteBuffers(1, &pointsVBO);
}

void Points::init() {
    clearData();

    core->glGenBuffers(1, &pointsVBO);
    core->glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
    core->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D) * data.size(),
                       data.data(), GL_STATIC_DRAW);
    core->glBindBuffer(GL_ARRAY_BUFFER, 0);

    core->glGenVertexArrays(1, &pointsVAO);
    core->glBindVertexArray(pointsVAO);

    core->glEnableVertexAttribArray(0);
    core->glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);

    core->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
                                2 * sizeof(float), (void*) nullptr);

    core->glBindVertexArray(0);
}

void Points::drawPoints() {
    core->glBindVertexArray(pointsVAO);
    core->glDrawArrays(GL_POINTS, 0, data.size());
    core->glBindVertexArray(0);
}

