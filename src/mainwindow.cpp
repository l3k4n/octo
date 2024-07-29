#include "mainwindow.h"

#include <QApplication>
#include <QBoxLayout>
#include <QWidget>

#include "widgets/navbar.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *main_layout = new QVBoxLayout();

    Octo::Widgets::Navbar *nav_bar = new Octo::Widgets::Navbar(this);
    main_layout->addWidget(nav_bar);
    main_layout->addStretch();
    main_layout->setContentsMargins(0, 0, 0, 0);

    setStyleSheet("background-color: green");
    setLayout(main_layout);
}
