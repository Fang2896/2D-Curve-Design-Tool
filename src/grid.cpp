//
// Created by fangl on 2023/9/11.
//

#include "grid.h"

Grid::Grid(int w, int h) {
    width = w;
    height = h;
    gridVAO = 0;
    gridVBO = 0;
    core = QOpenGLContext::currentContext()
               ->versionFunctions<QOpenGLFunctions_4_3_Core>();
}

Grid::~Grid() {
    core->glDeleteBuffers(1, &gridVBO);
}

void Grid::init() {
    height *= 10;
    width *= 10;

    data.clear();

    // horizontal
    for (int i = 0; i <= height / 2; i += 100) {
        data.push_back(QVector2D{-(float)width / 2, (float)i});
        data.push_back(QVector2D{(float)width / 2, (float)i});
        data.push_back(QVector2D{-(float)width / 2, (float)-i});
        data.push_back(QVector2D{(float)width / 2, (float)-i});

        //        normalizedData.push_back(QVector2D{-1.0f, (float)i * 2 / height});
        //        normalizedData.push_back(QVector2D{1.0f, (float)i * 2 / height});
        //        normalizedData.push_back(QVector2D{-1.0f, (float)-i * 2 / height});
        //        normalizedData.push_back(QVector2D{1.0f, (float)-i * 2 / height});
    }

    // vertical
    for (int i = 0; i <= width / 2; i += 100) {
        data.push_back(QVector2D{(float)i, -(float)height / 2});
        data.push_back(QVector2D{(float)i, (float)height / 2});
        data.push_back(QVector2D{(float)-i, -(float)height / 2});
        data.push_back(QVector2D{(float)-i, (float)height / 2});

        //        normalizedData.push_back(QVector2D{(float)i * 2 / width, -1.0f});
        //        normalizedData.push_back(QVector2D{(float)i * 2 / width, 1.0f});
        //        normalizedData.push_back(QVector2D{(float)-i * 2 / width, -1.0f});
        //        normalizedData.push_back(QVector2D{(float)-i * 2 / width, 1.0f});
    }

    core->glGenBuffers(1, &gridVBO);
    core->glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
    core->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D) * data.size(),
                       data.data(), GL_STATIC_DRAW);

    core->glGenVertexArrays(1, &gridVAO);
    core->glBindVertexArray(gridVAO);

    core->glEnableVertexAttribArray(0);
    core->glBindBuffer(GL_ARRAY_BUFFER, gridVBO);

    core->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),
                                (void*)nullptr);

    core->glBindVertexArray(0);
}

void Grid::drawGrid() {
    core->glBindVertexArray(gridVAO);
    core->glLineWidth(1.0f);
    core->glDrawArrays(GL_LINES, 0, data.size());
    core->glBindVertexArray(0);
}
