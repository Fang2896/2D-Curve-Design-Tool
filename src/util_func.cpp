//
// Created by fangl on 2023/9/11.
//

#include "util_func.h"


std::tuple<Eigen::VectorXd, Eigen::VectorXd> UtilFunc::convertPoints(const QVector<QVector2D> &points) {
    int n = points.size();
    Eigen::VectorXd xvals(n), yvals(n);
    for(int i = 0; i < n; i++) {
        xvals[i] = points[i].x();
        yvals[i] = points[i].y();
    }

    return std::make_tuple(xvals, yvals);
}

Eigen::VectorXd UtilFunc::polynomialInterpolateCoeff(const Eigen::VectorXd &xvals, const Eigen::VectorXd &yvals) {
    int n = (int)xvals.size();
    Eigen::MatrixXd A(n, n);

    // Create the Vandermonde matrix
    for (int i = 0; i < n; ++i)
        A.col(i) = xvals.array().pow(i);

    // Solve the least squares problem
    return A.colPivHouseholderQr().solve(yvals);
}
