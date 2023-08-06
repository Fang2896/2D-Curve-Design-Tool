//
// Created by fangl on 2023/6/6.
//

#ifndef HW1_MAINWINDOW_H
#define HW1_MAINWINDOW_H

#include <QTimer>
#include <QWidget>
#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QDoubleSpinBox>

#include "OGLManager.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    OGLManager *oglmanger;

    QLabel *titleLabel;
    QLabel *sigmaLabel;
    QLabel *orderLabel;
    QLabel *lambdaLabel;
    QLabel *resLabel;

    QDoubleSpinBox *sigmaSpinBox;
    QDoubleSpinBox *orderSpinBox;
    QDoubleSpinBox *lambdaSpinBox;
    QDoubleSpinBox *resSpinBox;

    QPushButton *polynomialInterpolateButton;
    QPushButton *gaussianInterpolateButton;
    QPushButton *polynomialRegressionButton;
    QPushButton *clearCanvasButton;

    void ConfigureLayout();

private slots:
    void onPolyInterCurvePushButton();
    void onGaussianInterCurvePushButton();
    void onGaussianInterSigmaSpinBox();
    void onClearCanvasPushButton();
    void onResolutionSpinBox();
    void onPolyRegreCurvePushButton();
    void onPolyRegreCurveOrderSpinBox();
    void onPolyRegreCurveLambdaSpinBox();

};


#endif //HW1_MAINWINDOW_H
