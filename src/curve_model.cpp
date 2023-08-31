//
// Created by fangl on 2023/8/31.
//

#include "curve_model.h"


const QVector<Point> &CurveModel::getPoints() const {
    return m_points;
}

void CurveModel::addPoint(const Point& point) {
    m_points.append(point);
}

void CurveModel::removePoint(const Point& point) {
    int index = m_points.indexOf(point);
    if(index != -1)
        m_points.remove(index);

}


