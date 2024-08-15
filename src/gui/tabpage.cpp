#include "tabpage.h"

#include <QBoxLayout>
#include <QIcon>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

#include "Tab.h"
#include "navbarbutton.h"

using namespace octo;
using namespace octo::gui;

TabPage::TabPage(const core::Tab &_tab, QWidget *parent) : QWidget(parent), tab(_tab) {
    setupNavBarWidgets();

    QWidget *navbar = new QWidget(this);
    QHBoxLayout *navbarLayout = new QHBoxLayout(navbar);
    navbar->setLayout(navbarLayout);
    navbar->setObjectName("NavBar");
    navbar->setContentsMargins(5, 5, 5, 5);
    navbarLayout->setContentsMargins(0, 0, 0, 0);
    navbarLayout->setSpacing(5);

    navbarLayout->addWidget(navBackBtn);
    navbarLayout->addWidget(navNextBtn);
    navbarLayout->addWidget(navRefreshBtn);
    navbarLayout->addWidget(addressBar);

    QVBoxLayout *windowLayout = new QVBoxLayout(this);
    windowLayout->setContentsMargins(0, 0, 0, 0);
    windowLayout->addWidget(navbar);
    windowLayout->addStretch();
    setLayout(windowLayout);
}

void TabPage::setupNavBarWidgets() {
    navBackBtn = new NavBarButton(":icons/arrow-left-solid.png", this);
    navNextBtn = new NavBarButton(":icons/arrow-right-solid.png", this);
    navRefreshBtn = new NavBarButton(":icons/rotate-right-solid.png", this);
    addressBar = new QLineEdit(tab.url());

    navBackBtn->setFixedSize(btnSize);
    navNextBtn->setFixedSize(btnSize);
    navRefreshBtn->setFixedSize(btnSize);
    navBackBtn->setIconSize(iconSize);
    navNextBtn->setIconSize(iconSize);
    navRefreshBtn->setIconSize(iconSize);

    addressBar->setFixedHeight(addressBarHeight);
    addressBar->setObjectName("NavBarAddrInput");
    addressBar->setPlaceholderText("Enter address");

    // no history by default, so buttons are disabled
    navBackBtn->setEnabled(false);
    navNextBtn->setEnabled(false);
};
