//
// Created by fangl on 2023/8/31.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>

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
    void onDisplayPolyInterCurve();

// private variables
private:
    Ui::MainWindow *ui;

    CurveModel m_model;
    GLRenderer *m_glRenderer;

    // widgets
    QStackedWidget *m_curveControlStackedWidget;
    QLabel *m_titleLabel;
    QPushButton *m_polyInterButton;
    QPushButton *m_clearButton;

// private function
private:
    void configureLayout();
    void connectSignal();
};


#endif //MAINWINDOW_H
