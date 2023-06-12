//
// Created by fangl on 2023/6/12.
//

#ifndef HW1_ALGORITHMS_H
#define HW1_ALGORITHMS_H

#include <Eigen/Dense>
#include <QVector>
#include <QVector2D>


class Algorithms
{
public:
    static std::tuple<Eigen::VectorXd, Eigen::VectorXd>
            convertPoints(const QVector<QVector2D> &points);

    static Eigen::VectorXd polynomialFit(const Eigen::VectorXd &xvals, const Eigen::VectorXd &yvals,
                                         int order);

private:
    Algorithms() {}

};


#endif //HW1_ALGORITHMS_H
