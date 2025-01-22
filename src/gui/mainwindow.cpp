#include "mainwindow.h"

#include <QTabBar>
#include <QTabWidget>

#include "tabbar.h"
#include "tabpage.h"

MainWindow::MainWindow(QWidget* parent) : QTabWidget(parent) {
    setObjectName("MainWindow");
    setTabsClosable(true);
    setTabBar(new TabBar(this));

    connect(this, &QTabWidget::tabCloseRequested, this, &MainWindow::tabCloseRequested);

    createTab();
}

void MainWindow::createTab() { addTab(new TabPage(this), "New Tab"); }

void MainWindow::tabCloseRequested(int idx) { removeTab(idx); }
