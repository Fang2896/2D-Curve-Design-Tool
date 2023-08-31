//
// Created by fangl on 2023/8/31.
//

#ifndef CURVE_MODEL_H
#define CURVE_MODEL_H

#include <QVector>

#include "point.h"


enum class CurveType {
    fittingCurve,
    parameterizationCurve,
    bezierCurve
};


class CurveModel
{
public:
    CurveModel() = default;

    const QVector<Point>& getPoints() const;
    void addPoint(const Point& point);
    void removePoint(const Point& point);

    // class 1 : fitting curve
    QVector<QVector3D> polynomialInterpolationCurve() const;
    QVector<QVector3D> gaussianRBFInterpolationCurve() const;
    QVector<QVector3D> polynomialRegressionCurve() const;

    // class 2 : parameterization curve
    QVector<QVector3D> uniformParameterizedCurve() const;
    QVector<QVector3D> chordalParameterizedCurve() const;
    QVector<QVector3D> centripetalParameterizedCurve() const;

    // class 3 : bezier curve
    QVector<QVector3D> bezierCurve() const;

private:
    QVector<Point> m_points;
    // 其他曲线相关数据
};


#endif //CURVE_MODEL_H
