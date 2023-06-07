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
    QLabel *spanLabel;
    QLabel *lambdaLabel;

    QDoubleSpinBox *sigmaSpinBox;
    QDoubleSpinBox *spanSpinBox;
    QDoubleSpinBox *lambdaSpinBox;

    QPushButton *polynomialFittingButton;
    QPushButton *gaussianFittingButton;
    QPushButton *polynomialRegressionButton;
    QPushButton *ridgeRegressionButton;
    QPushButton *allButton;
    QPushButton *clearCanvasButton;

    void AddLayout();

private slots:
    void onClearCanvasPushButton();


};


#endif //HW1_MAINWINDOW_H
