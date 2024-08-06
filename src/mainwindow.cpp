#include "mainwindow.h"

#include <qlogging.h>
#include <qwidget.h>

#include <QApplication>
#include <QBoxLayout>
#include <QListView>
#include <QStackedWidget>
#include <QStandardItemModel>

#include "gui/tabbar.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    auto model = new QStandardItemModel(this);
    model->appendRow(new QStandardItem("New Tab"));

    QListView *tab_bar = new octo::gui::TabBarView(this);
    tab_bar->setModel(model);
    tab_bar->setCurrentIndex(model->index(0, 0));

    QStackedWidget *tab_stack = new QStackedWidget(this);
    tab_stack->addWidget(new QWidget);

    QVBoxLayout *main_layout = new QVBoxLayout(this);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->addWidget(tab_bar);
    main_layout->addWidget(tab_stack);

    setStyleSheet("background-color: #111; border: none;");
    setLayout(main_layout);
}
