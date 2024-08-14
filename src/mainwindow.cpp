#include "mainwindow.h"

#include <QTabWidget>

#include "Window.h"
#include "tabbar.h"
#include "tabpage.h"

using namespace octo;

MainWindow::MainWindow(QWidget* parent) : QTabWidget(parent), window(core::Window(this)) {
    setObjectName("MainWindow");
    setTabsClosable(true);
    setTabBar(new gui::TabBar(this));

    connect(&window, &core::Window::newTabCreated, this, &MainWindow::createTab);

    window.newTab();
}

void MainWindow::createTab(const octo::core::Tab& tab, size_t pos) {
    addTab(new gui::TabPage(tab, this), tab.title());
}
