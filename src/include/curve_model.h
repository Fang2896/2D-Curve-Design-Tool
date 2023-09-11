//
// Created by fangl on 2023/8/31.
//

#ifndef CURVE_MODEL_H
#define CURVE_MODEL_H

#include <QVector>
#include <QVector2D>

#include <memory>

#include "point.h"


enum class CurveType {
    fittingCurve,
    parameterizationCurve,
    bezierCurve
};


class CurveModel
{
public:
    CurveModel() {
        m_points = std::make_unique<Points>();
    }

    // public data


    void clearData();

    int getPointsSize();
    const QVector2D* getPointsData() const;
    const QVector3D* getColorsData() const;

    void setPointPosition(int index, QVector2D position);
    void setPointColor(int index, QVector3D pointColor);

    void addPoint(QVector2D pos);
    int findNearestPointInRange(QVector2D clickPos, float radius);

    // class 1 : fitting curve
    QVector<QVector2D> getPolynomialInterpolationCurve() const;
    QVector<QVector2D> getGaussianRBFInterpolationCurve() const;
    QVector<QVector2D> getPolynomialRegressionCurve() const;

    // class 2 : parameterization curve
    QVector<QVector2D> getUniformParameterizedCurve() const;
    QVector<QVector2D> getChordalParameterizedCurve() const;
    QVector<QVector2D> getCentripetalParameterizedCurve() const;

    // class 3 : bezier curve
    QVector<QVector2D> getBezierCurve() const;

private:
    // QVector<Point> m_points;
    std::unique_ptr<Points> m_points;

    // 其他曲线相关数据
    // ...

};


#endif //CURVE_MODEL_H
