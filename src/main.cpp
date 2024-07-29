#include <QApplication>
#include <QFile>
#include <QString>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow main_window(nullptr);

    main_window.show();
    return app.exec();
}
