#include "gui/tabpage.h"

#include <QVBoxLayout>
#include <QWidget>

#include "gui/navbar.h"

TabPage::TabPage(QWidget* parent) : QWidget(parent) {
    NavBar* navbar = new NavBar(this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(navbar);
    layout->addStretch();
    setLayout(layout);
}
