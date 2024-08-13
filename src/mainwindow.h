#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QTabWidget>

class MainWindow : public QTabWidget {
    Q_OBJECT;

public:
    MainWindow(QWidget *parent = nullptr);
};

#endif  // !MAIN_WINDOW_H
