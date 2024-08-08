#include "mainwindow.h"

#include <QBoxLayout>
#include <QStackedWidget>
#include <QStandardItemModel>

#include "gui/browserwindow.h"
#include "gui/tabbar.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    auto model = new QStandardItemModel(this);
    model->appendRow(new QStandardItem("New Tab"));

    QListView *tab_bar = new octo::gui::TabBarView(this);
    tab_bar->setModel(model);
    tab_bar->setCurrentIndex(model->index(0, 0));

    QStackedWidget *tab_stack = new QStackedWidget(this);
    tab_stack->addWidget(new octo::gui::BrowserWindow(QPersistentModelIndex(model->index(0, 0))));

    QVBoxLayout *main_layout = new QVBoxLayout(this);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    main_layout->addWidget(tab_bar);
    main_layout->addWidget(tab_stack);

    main_layout->addStretch();
    setLayout(main_layout);
}
