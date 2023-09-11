//
// Created by fangl on 2023/8/31.
//

#ifndef CURVE_MODEL_H
#define CURVE_MODEL_H

#include <QVector>
#include <QVector2D>

#include <memory>
#include <Eigen/Dense>

#include "point.h"
#include "util_func.h"


enum class CurveType {
    fittingCurve,
    parameterizationCurve,
    bezierCurve
};


class CurveModel
{
public:
    CurveModel(int w, int h)
        : width(w), height(h)
    {
        m_points = std::make_unique<Points>();
        resolution = 5000;
    }

    // public variables

    void clearData();
    void setResolution(int res);

    int getPointsSize();
    const QVector2D* getPointsData() const;
    const QVector3D* getColorsData() const;

    void setPointPosition(int index, QVector2D position);
    void setPointColor(int index, QVector3D pointColor);

    void addPoint(QVector2D pos);
    int findNearestPointInRange(QVector2D clickPos, float radius);

    // curve data getter and setter and updater
    // class 1 : fitting curve
    // TODO: 这些curve可以整合为一个类中去，这些方法就不用一直写了
    //  还可以在CurveModel里面进行一个是否显示的判断
    void updatePolyInterCurveData();
    const QVector<QVector2D>& getPolyInterCurveData() const;
    bool getPolyInterCurveStatus();
    int getPolyInterCurveDataSize();
    void setPolyInterCurveStatus(bool status);


private:
    // QVector<Point> m_points;
    std::unique_ptr<Points> m_points;

    QVector<QVector2D> m_polyInterCurveData;

    int width;
    int height;
    int resolution;

    // display curve booleans
    bool displayPolyInterCurve = false;
};


#endif //CURVE_MODEL_H
