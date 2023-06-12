//
// Created by fangl on 2023/6/12.
//

#include "Algorithms.h"


std::tuple<Eigen::VectorXd, Eigen::VectorXd> Algorithms::convertPoints(const QVector<QVector2D> &points) {
    int n = points.size();
    Eigen::VectorXd xvals(n), yvals(n);
    for(int i = 0; i < n; i++) {
        xvals[i] = points[i].x();
        yvals[i] = points[i].y();
    }

    return std::make_tuple(xvals, yvals);
}

Eigen::VectorXd Algorithms::polynomialFit(const Eigen::VectorXd &xvals, const Eigen::VectorXd &yvals, int order) {
    int n = (int)xvals.size();
    Eigen::MatrixXd A(n, order + 1);

    // Create the Vandermonde matrix
    for (int i = 0; i <= order; ++i)
        A.col(i) = xvals.array().pow(i);

    // Solve the least squares problem
    auto qr = A.householderQr();
    auto result = qr.solve(yvals);

    return result;
}
