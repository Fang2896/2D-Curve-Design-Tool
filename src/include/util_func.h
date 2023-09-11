//
// Created by fangl on 2023/9/11.
//

#ifndef UTIL_FUNC_H
#define UTIL_FUNC_H

#include <Eigen/Dense>
#include <QVector>
#include <QVector2D>


class UtilFunc
{
public:
    static std::tuple<Eigen::VectorXd, Eigen::VectorXd>
        convertPoints(const QVector<QVector2D> &points);

    static Eigen::VectorXd polynomialInterpolateCoeff(const Eigen::VectorXd &xvals,
                                                      const Eigen::VectorXd &yvals);

private:
    UtilFunc() {}
};


#endif //UTIL_FUNC_H
