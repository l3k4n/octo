#ifndef GUI_MAIN_WINDOW_H
#define GUI_MAIN_WINDOW_H

#include <QTabWidget>

#include "core/Window.h"
#include "core/Tab.h"

class MainWindow : public QTabWidget {
    Q_OBJECT;

public:
    MainWindow(QWidget* parent = nullptr);

public slots:
    void createTab(Core::Tab& tab);
    void tabMoved(int from, int to);
    void tabCloseRequested(int idx);

private:
    Core::Window window;
};

#endif  // !GUI_MAIN_WINDOW_H
