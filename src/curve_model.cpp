//
// Created by fangl on 2023/8/31.
//

#include "curve_model.h"

void CurveModel::clearData() {
    m_points->clearData();

}

int CurveModel::getPointsSize() {
    return m_points->getPointsSize();
}

const QVector2D* CurveModel::getPointsData() const {
    return m_points->getPointsData().data();
}

const QVector3D* CurveModel::getColorsData() const {
    return m_points->getPointsColorData().data();
}

void CurveModel::setPointPosition(int index, QVector2D position) {
    m_points->setPointPosition(index, position);
}

void CurveModel::setPointColor(int index, QVector3D pointColor) {
    m_points->setPointColor(index, pointColor);
}

void CurveModel::addPoint(QVector2D pos) {
    m_points->addPoint(pos);

    // 是否要更新曲线？这里可以做判断

}

// find the nearest point index among radius
// if not find, return -1
int CurveModel::findNearestPointInRange(QVector2D clickPos, float radius) {
    const QVector<QVector2D> &positions = m_points->getPointsData();

    if(positions.isEmpty()) {
        return -1;
    }

    int nearestPointIndex = -1;
    float minDist = radius;
    for(int i = 0; i < positions.size(); i++) {
        float dist = clickPos.distanceToPoint(positions[i]);
        if(dist < radius && dist < minDist) {
            minDist = dist;
            nearestPointIndex = i;
        }
    }

    return nearestPointIndex;
}


