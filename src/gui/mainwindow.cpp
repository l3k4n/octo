#include "gui/mainwindow.h"

#include <QTabBar>
#include <QTabWidget>
#include <QtGlobal>

#include "core/Window.h"
#include "gui/tabbar.h"
#include "gui/tabpage.h"

MainWindow::MainWindow(QWidget* parent) : QTabWidget(parent), window(Core::Window(this)) {
    setObjectName("MainWindow");
    setTabsClosable(true);
    setTabBar(new TabBar(this));

    connect(&window, &Core::Window::newTabCreated, this, &MainWindow::createTab);
    connect(tabBar(), &QTabBar::tabMoved, this, &MainWindow::tabMoved);
    connect(this, &QTabWidget::tabCloseRequested, this, &MainWindow::tabCloseRequested);

    window.newTab();
}

void MainWindow::createTab(Core::Tab& tab) {
    int idx = addTab(new TabPage(tab, this), tab.title());
    Q_ASSERT_X(idx == tab.position(), "MainWindow::createTab",
               "Some how tab position got mixed up");

    connect(&tab, &Core::Tab::urlChanged, [this, &tab](const QString& url) {
        // use url as title until content loads and real title is set
        tabBar()->setTabText(tab.position(), url);
    });

    connect(&tab, &Core::Tab::titleChanged,
            [this, &tab](const QString& title) { tabBar()->setTabText(tab.position(), title); });
}

void MainWindow::tabMoved(int from, int to) { window.moveTab(from, to); }

void MainWindow::tabCloseRequested(int idx) { window.closeTab(idx); }
