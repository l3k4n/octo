#include "navbar.h"

#include <QBoxLayout>
#include <QPainter>
#include <QWidget>

using Navbar = Octo::Widgets::Navbar;

Navbar::Navbar(QWidget *parent) : QWidget(parent), navbar_layout(new QHBoxLayout) {
    url_input = new QLineEdit("https://www.google.com", parent);
    navbar_layout->addWidget(url_input);

    setLayout(navbar_layout);
}

void Navbar::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setBrush(QBrush(QColor("#ff0000")));
    painter.setPen(Qt::PenStyle::NoPen);
    painter.drawRect(this->rect());
}
