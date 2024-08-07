#include "browserwindow.h"

#include <qobject.h>
#include <qpushbutton.h>

#include <QBoxLayout>
#include <QLineEdit>
#include <QPersistentModelIndex>
#include <QPushButton>
#include <QWidget>

using namespace octo::gui;

const int NAV_BTN_SIZE = 25;

inline QPushButton *createNavButton(const QString &str, const QSize &size) {
    auto btn = new QPushButton(str);
    btn->setFixedSize(size);

    return btn;
}

BrowserWindow::BrowserWindow(QPersistentModelIndex idx, QWidget *parent)
    : QWidget(parent), model_index(idx) {
    const auto size = QSize(NAV_BTN_SIZE, NAV_BTN_SIZE);
    navBackBtn = createNavButton("<-", size);
    navNextBtn = createNavButton("->", size);
    navRefreshBtn = createNavButton("O", size);
    addressBar = new QLineEdit("https://www.google.com");
    addressBar->setFixedHeight(NAV_BTN_SIZE);

    QWidget *navbar = new QWidget(this);
    QHBoxLayout *navbarLayout = new QHBoxLayout(navbar);
    navbar->setContentsMargins(5, 5, 5, 5);
    navbarLayout->setContentsMargins(0, 0, 0, 0);
    navbarLayout->setSpacing(5);
    navbar->setStyleSheet(
        "QWidget { background-color: #222; }"
        "QPushButton, QLineEdit { background-color: #111; color: #fff; }");
    navbarLayout->addWidget(navBackBtn);
    navbarLayout->addWidget(navNextBtn);
    navbarLayout->addWidget(navRefreshBtn);
    navbarLayout->addWidget(addressBar);
    navbar->setLayout(navbarLayout);

    QVBoxLayout *windowLayout = new QVBoxLayout(this);
    windowLayout->setContentsMargins(0, 0, 0, 0);
    windowLayout->addWidget(navbar);
    windowLayout->addStretch();
    setParent(parent);
    setLayout(windowLayout);
    setStyleSheet("background-color: #222; border-radius: 2px");
}
