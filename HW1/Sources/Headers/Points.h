//
// Created by fangl on 2023/6/7.
//

#ifndef HW1_POINTS_H
#define HW1_POINTS_H

#include <QVector2D>
#include <QOpenGLFunctions_3_3_Core>

class Points
{
public:
    Points();
    ~Points();

    void init();
    void drawPoints();

    auto getData() -> QVector2D* {
        return data.data();
    }

    auto addPoint(float x, float y) -> void {
        data.push_back({x, y});
        // 更新数据，重新传入GPU（可以考虑改善）
        core->glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
        core->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D) * data.size(), data.data(), GL_STATIC_DRAW);
        core->glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    auto addPoint(QVector2D point) -> void {
        data.push_back(point);
        core->glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
        core->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D) * data.size(), data.data(), GL_STATIC_DRAW);
        core->glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    auto getPointNumber() -> GLuint {
        return data.size();
    }

    auto clearData() -> void {
        data.clear();
    }

private:
    QOpenGLFunctions_3_3_Core *core;
    GLuint pointsVBO;

    QVector<QVector2D> data;

};


#endif //HW1_POINTS_H
