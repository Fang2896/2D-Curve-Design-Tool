//
// Created by fangl on 2023/8/31.
//

#include "curve_model.h"

void CurveModel::clearData() {
    m_points->clearData();

}

void CurveModel::setResolution(int res) {
    resolution = res;
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

void CurveModel::updatePolyInterCurveData() {
    m_polyInterCurveData.clear();

    if(m_points->getPointsSize() < 2) {
        return;
    }

    Eigen::VectorXd xvals, yvals;
    std::tie(xvals, yvals) = UtilFunc::convertPoints(m_points->getPointsData());
    Eigen::VectorXd coeffs = UtilFunc::polynomialInterpolateCoeff(xvals, yvals);

    // sample points
    double step = (double)width / (double)resolution;
    for(int i = 0; i <= resolution; i++) {
        double x = -(float)width / 2.0f + i * step;
        double y = 0;
        for(int j = 0; j < xvals.size(); j++) {
            y += coeffs[j] * std::pow(x, j);
        }
        m_polyInterCurveData.push_back(QVector2D(x, y));
    }

}

const QVector<QVector2D>& CurveModel::getPolyInterCurveData() const {
    return m_polyInterCurveData;
}

// boolean functions
bool CurveModel::getPolyInterCurveStatus() {
    return displayPolyInterCurve;
}

int CurveModel::getPolyInterCurveDataSize() {
    return m_polyInterCurveData.size();
}

void CurveModel::setPolyInterCurveStatus(bool status) {
    displayPolyInterCurve = status;
}




