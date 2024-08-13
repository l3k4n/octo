#include <QBoxLayout>
#include <QIcon>
#include <QLineEdit>
#include <QPersistentModelIndex>
#include <QPushButton>
#include <QWidget>

#include "OctoInstanceModel.h"
#include "tabpage.h"
#include "utils.h"

using namespace octo;
using namespace octo::gui;

const int NAV_BTN_SIZE = 30;
const int NAV_ICON_SIZE = 15;

inline QPushButton *createNavButton(const QString &iconPath, const QSize &size) {
    QIcon icon;
    QPixmap enabled_pixmap = octo::utils::createColoredPixmap(iconPath, "#fff", "#ccc");
    icon.addPixmap(enabled_pixmap, QIcon::Mode::Active);
    QPixmap disabled_pixmap = octo::utils::createColoredPixmap(iconPath, "#fff", "#333");
    icon.addPixmap(disabled_pixmap, QIcon::Mode::Disabled);

    auto btn = new QPushButton;
    btn->setIcon(icon);
    btn->setFixedSize(size);
    btn->setIconSize(QSize(NAV_ICON_SIZE, NAV_ICON_SIZE));

    return btn;
}

TabPage::TabPage(QPersistentModelIndex idx, QWidget *parent) : QWidget(parent), modelIndex(idx) {
    const auto size = QSize(NAV_BTN_SIZE, NAV_BTN_SIZE);
    navBackBtn = createNavButton(":icons/arrow-left-solid.png", size);
    navNextBtn = createNavButton(":icons/arrow-right-solid.png", size);
    navRefreshBtn = createNavButton(":icons/rotate-right-solid.png", size);
    addressBar = new QLineEdit(idx.data(models::OctoInstanceModel::UrlRole).toString());
    addressBar->setFixedHeight(NAV_BTN_SIZE);

    // no history by default, so buttons are disabled
    navBackBtn->setEnabled(false);
    navNextBtn->setEnabled(false);

    QWidget *navbar = new QWidget(this);
    QHBoxLayout *navbarLayout = new QHBoxLayout(navbar);
    navbar->setContentsMargins(5, 2, 5, 5);
    navbarLayout->setContentsMargins(0, 0, 0, 0);
    navbarLayout->setSpacing(5);
    navbarLayout->addWidget(navBackBtn);
    navbarLayout->addWidget(navNextBtn);
    navbarLayout->addWidget(navRefreshBtn);
    navbarLayout->addWidget(addressBar);
    navbar->setLayout(navbarLayout);
    navbar->setObjectName("NavBar");

    QVBoxLayout *windowLayout = new QVBoxLayout(this);
    windowLayout->setContentsMargins(0, 0, 0, 0);
    windowLayout->addWidget(navbar);
    windowLayout->addStretch();
    setParent(parent);
    setLayout(windowLayout);
}
