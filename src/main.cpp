#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QString>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow(nullptr);

    // load global stylesheet
    QFile file(":styles/global.qss");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        app.setStyleSheet(QLatin1String(file.readAll()));
        file.close();
    } else {
        qDebug() << "Failed to open stylesheet at" << file.fileName();
    }

    mainWindow.show();
    return app.exec();
}
