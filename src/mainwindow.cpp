#include "mainwindow.h"

#include <QTabBar>
#include <QTabWidget>
#include <QtGlobal>

#include "Window.h"
#include "tabbar.h"
#include "tabpage.h"

using namespace octo;

MainWindow::MainWindow(QWidget* parent) : QTabWidget(parent), window(core::Window(this)) {
    setObjectName("MainWindow");
    setTabsClosable(true);
    setTabBar(new gui::TabBar(this));

    connect(&window, &core::Window::newTabCreated, this, &MainWindow::createTab);
    connect(tabBar(), &QTabBar::tabMoved, this, &MainWindow::tabMoved);
    connect(this, &QTabWidget::tabCloseRequested, this, &MainWindow::tabCloseRequested);

    window.newTab();
}

void MainWindow::createTab(const octo::core::Tab& tab) {
    int idx = addTab(new gui::TabPage(tab, this), tab.title());
    Q_ASSERT_X(idx == tab.position(), "MainWindow::createTab",
               "Some how tab position got mixed up");
}

void MainWindow::tabMoved(int from, int to) { window.moveTab(from, to); }

void MainWindow::tabCloseRequested(int idx) { window.closeTab(idx); }
