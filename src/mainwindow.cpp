#include "mainwindow.h"

#include <QBoxLayout>
#include <QStackedWidget>
#include <QStandardItemModel>

#include "gui/browserwindow.h"
#include "gui/tabbar.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    auto model = new QStandardItemModel(this);
    model->appendRow(new QStandardItem("New Tab"));

    QListView *tabBar = new octo::gui::TabBarView(this);
    tabBar->setModel(model);
    tabBar->setCurrentIndex(model->index(0, 0));

    QStackedWidget *tabStack = new QStackedWidget(this);
    tabStack->addWidget(new octo::gui::BrowserWindow(QPersistentModelIndex(model->index(0, 0))));

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mainLayout->addWidget(tabBar);
    mainLayout->addWidget(tabStack);

    mainLayout->addStretch();
    setLayout(mainLayout);
}
