#include "navbar.h"

#include <QHBoxLayout>
#include <QPainter>
#include <QStyleOption>

#include "navbarbutton.h"

NavBar::NavBar(QWidget* parent) : QWidget(parent) {
    NavBarButton* navBackBtn = new NavBarButton(":icons/navigate-back.png", this);
    NavBarButton* navNextBtn = new NavBarButton(":icons/navigate-next.png", this);
    NavBarButton* navRefreshBtn = new NavBarButton(":icons/refresh.png", this);
    QLineEdit* addressBar = new QLineEdit;

    navBackBtn->setFixedSize(btnSize);
    navNextBtn->setFixedSize(btnSize);
    navRefreshBtn->setFixedSize(btnSize);
    navBackBtn->setIconSize(iconSize);
    navNextBtn->setIconSize(iconSize);
    navRefreshBtn->setIconSize(iconSize);
    addressBar->setFixedHeight(addressBarHeight);
    addressBar->setObjectName("NavBarAddrInput");

    // set defaults
    navBackBtn->setEnabled(false);
    navNextBtn->setEnabled(false);
    addressBar->setPlaceholderText("Enter address");

    QHBoxLayout* navbarLayout = new QHBoxLayout(this);
    navbarLayout->setContentsMargins(0, 0, 0, 0);
    navbarLayout->setSpacing(5);
    navbarLayout->addWidget(navBackBtn);
    navbarLayout->addWidget(navNextBtn);
    navbarLayout->addWidget(navRefreshBtn);
    navbarLayout->addWidget(addressBar);

    connect(navBackBtn, &QPushButton::clicked, this, &NavBar::backClicked);
    connect(navNextBtn, &QPushButton::clicked, this, &NavBar::nextClicked);
    connect(navRefreshBtn, &QPushButton::clicked, this, &NavBar::refreshClicked);
    connect(addressBar, &QLineEdit::returnPressed,
            [addressBar, this]() { emit urlSubmitted(addressBar->text()); });

    setContentsMargins(5, 5, 5, 5);
    setAutoFillBackground(true);
    setObjectName("NavBar");
    setLayout(navbarLayout);
}

void NavBar::paintEvent(QPaintEvent*) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void NavBar::setUrl(const QString& url) { addressBar->setText(url); }

void NavBar::setBackButtonEnabled(bool enabled) { navBackBtn->setEnabled(enabled); };

void NavBar::setNextButtonEnabled(bool enabled) { navNextBtn->setEnabled(enabled); };
