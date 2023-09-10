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

const QColor* CurveModel::getColorsData() const {
    return m_points->getPointsColorData().data();
}

void CurveModel::setPointColor(int index, QColor pointColor) {
    m_points->setPointColor(index, pointColor);
}

void CurveModel::addPoint(QVector2D pos) {
    m_points->addPoint(pos);

    // 是否要更新曲线？这里可以做判断

}

// TODO:
int CurveModel::findRangePoint(QVector2D clickPos) {
    const QVector<QVector2D> &positions = m_points->getPointsData();

    if(positions.isEmpty()) {
        return -1;
    }

    int nearestPointIndex = 0;


    return nearestPointIndex;

}


