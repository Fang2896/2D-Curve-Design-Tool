#include <QApplication>
#include "mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    QFile file(":/resources/qss/flatwhite.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(styleSheet);

    MainWindow w;
    w.show();
    return QApplication::exec();
}
