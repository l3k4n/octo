#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QTabWidget>

#include "Window.h"

class MainWindow : public QTabWidget {
    Q_OBJECT;

public:
    MainWindow(QWidget *parent = nullptr);

private:
    octo::core::Window window;
};

#endif  // !MAIN_WINDOW_H
