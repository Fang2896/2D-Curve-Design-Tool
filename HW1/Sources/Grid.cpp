//
// Created by fangl on 2023/6/7.
//

#include "Grid.h"

Grid::Grid(int w, int h) {
    width = w;
    height = h;
    gridVBO = 0;
    core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
}

Grid::~Grid() {
    core->glDeleteBuffers(1, &gridVBO);
}

void Grid::init() {
    data.clear();
    // horizontal
    for(int i = -height / 2; i <= height / 2; i += 100) {

        data.push_back(QVector2D{-(float)width / 2, (float)i});
        data.push_back(QVector2D{(float)width / 2, (float)i});
        normalizedData.push_back(QVector2D{-1.0f, (float)i * 2 / height});
        normalizedData.push_back(QVector2D{1.0f, (float)i * 2 / height});
    }

    // vertical
    for(int i = -width / 2; i <= width / 2; i += 100) {
        data.push_back(QVector2D{(float)i, -(float)height / 2});
        data.push_back(QVector2D{(float)i, (float)height / 2});
        normalizedData.push_back(QVector2D{(float)i * 2 / width, -1.0f});
        normalizedData.push_back(QVector2D{(float)i * 2 / width, 1.0f});
    }

    core->glGenBuffers(1, &gridVBO);
    core->glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
    core->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D) * data.size(),
                       data.data(), GL_STATIC_DRAW);
}

void Grid::drawGrid() {
    core->glEnableVertexAttribArray(0);
    core->glBindBuffer(GL_ARRAY_BUFFER, gridVBO);

    core->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
                                2 * sizeof(float), (void*) nullptr);
    core->glDrawArrays(GL_LINES, 0, data.size());

    core->glBindBuffer(GL_ARRAY_BUFFER, 0);
}
