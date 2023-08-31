//
// Created by fangl on 2023/8/31.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui/ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::MainWindow), m_model()
{
    ui->setupUi(this);

    m_glRenderer = new GLRenderer(&m_model, this);

    configureLayout();
    connectSignal();
}

MainWindow::~MainWindow()
{
    delete ui;
}


/********** slot functions *************/
void MainWindow::switchCurveType(CurveType curveType) {

}



void MainWindow::configureLayout() {
    m_curveControlStackedWidget = ui->curveControlStackedWidget;
    m_titleLabel = ui->titleLabel;
    m_clearButton = ui->clearButton;
}

void MainWindow::connectSignal() {

}

