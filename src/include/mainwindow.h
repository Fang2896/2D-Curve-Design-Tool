//
// Created by fangl on 2023/8/31.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QDoubleSpinBox>

#include "curve_model.h"
#include "gl_renderer.h"


QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow: public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onClearCanvas();

    void updateResolution();
    void switchPage();

    void onDisplayPolyInterCurve();

    void onDisplayRBFInterCurve();
    void onUpdateRBFInterSigma();

    void onDisplayPolyRegreCurve();
    void onUpdatePolyRegreOrder();
    void onUpdatePolyRegreLambda();

    void onDisplayUniformParamCurve();
    void onDisplayChordalParamCurve();
    void onDisplayCentrietalParamCurve();

// private variables
private:
    Ui::MainWindow *ui;

    CurveModel m_model;
    GLRenderer *m_glRenderer;

    // widgets
    QStackedWidget *m_curveControlStackedWidget;
    int currentStackPage = 1;

    QWidget *m_paramPage;
    QWidget *m_interpolationPage;

    QLabel *m_titleLabel;
    QLabel *m_interPageLabel;
    QLabel *m_paramPageLabel;

    QLabel *m_RBFSigmaLabel;
    QLabel *m_polyRegreOrderLabel;
    QLabel *m_polyRegreLambdaLabel;

    QLabel *m_resolutionLabel;


    QPushButton *m_polyInterButton;
    QPushButton *m_RBFInterButton;
    QPushButton *m_polyRegreButton;

    QPushButton *m_uniformParamButton;
    QPushButton *m_chordalParamButton;
    QPushButton *m_centrietalParamButton;

    QPushButton *m_clearButton;
    QPushButton *m_pageSwitchButton;

    QDoubleSpinBox *m_RBFSigmaSpinBox;
    QDoubleSpinBox *m_polyRegreOrderSpinBox;
    QDoubleSpinBox *m_polyRegreLambdaSpinBox;

    QDoubleSpinBox *m_resolutionSpinBox;


// private function
private:
    void configureLayout();
    void connectSignal();
    void releaseAllButtons();

};


#endif //MAINWINDOW_H
