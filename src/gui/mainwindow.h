#ifndef GUI_MAIN_WINDOW_H
#define GUI_MAIN_WINDOW_H

#include <QTabWidget>

class MainWindow : public QTabWidget {
    Q_OBJECT;

public:
    MainWindow(QWidget* parent = nullptr);

public slots:
    void createTab();
    void tabCloseRequested(int idx);
};

#endif  // !GUI_MAIN_WINDOW_H
