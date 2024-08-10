#include "mainwindow.h"

#include <QBoxLayout>
#include <QStackedWidget>

#include "gui/browserwindow.h"
#include "gui/tabbar.h"
#include "models/OctoInstanceModel.h"

using namespace octo;

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    models::OctoInstanceModel *model = new models::OctoInstanceModel(this);

    gui::TabBarView *tabBar = new gui::TabBarView(this);
    tabBar->setModel(model);
    tabBar->setCurrentIndex(model->index(0, 0));

    QStackedWidget *tabStack = new QStackedWidget(this);
    tabStack->addWidget(new gui::BrowserWindow(model->index(0, 0)));

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mainLayout->addWidget(tabBar);
    mainLayout->addWidget(tabStack);

    mainLayout->addStretch();
    setLayout(mainLayout);
}
