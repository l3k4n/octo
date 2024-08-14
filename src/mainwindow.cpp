#include "mainwindow.h"

#include <QTabWidget>

#include "Window.h"
#include "tabbar.h"

using namespace octo;

MainWindow::MainWindow(QWidget* parent) : QTabWidget(parent), window(core::Window(this)) {
    setObjectName("MainWindow");
    setTabsClosable(true);
    setTabBar(new gui::TabBar(this));
}
