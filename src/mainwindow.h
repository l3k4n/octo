#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QTabWidget>

#include "Window.h"
#include "core/Tab.h"

class MainWindow : public QTabWidget {
    Q_OBJECT;

public:
    MainWindow(QWidget* parent = nullptr);

public slots:
    void createTab(const octo::core::Tab& tab, size_t pos);

private:
    octo::core::Window window;
};

#endif  // !MAIN_WINDOW_H
