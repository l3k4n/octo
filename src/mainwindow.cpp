#include "mainwindow.h"

#include <QTabWidget>

#include "models/OctoInstanceModel.h"
#include "tabbar.h"
#include "tabpage.h"

using namespace octo;

MainWindow::MainWindow(QWidget *parent) : QTabWidget(parent) {
    setObjectName("MainWindow");
    setTabsClosable(true);
    setTabBar(new gui::TabBar(this));

    models::OctoInstanceModel *model = new models::OctoInstanceModel(this);
    addTab(new gui::TabPage(model->index(0)), "New Tab");
}
