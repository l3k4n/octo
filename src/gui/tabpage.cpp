#include "gui/tabpage.h"

#include <QVBoxLayout>
#include <QWidget>

#include "core/Tab.h"
#include "gui/navbar.h"

TabPage::TabPage(Core::Tab &_tab, QWidget *parent) : QWidget(parent), tab(_tab) {
    NavBar *navbar = new NavBar(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(navbar);
    layout->addStretch();
    setLayout(layout);

    connect(navbar, &NavBar::urlSubmitted, [this](const QString &url) { tab.navigate(url); });
}
