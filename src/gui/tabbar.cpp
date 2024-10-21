#include "gui/tabbar.h"

#include <QPainter>
#include <QStyleOptionTab>
#include <QStylePainter>

TabBar::TabBar(QWidget* parent) : QTabBar(parent) { setObjectName("TabBar"); }

void TabBar::paintEvent(QPaintEvent*) {
    QStylePainter painter(this);
    QStyleOptionTab opt;

    for (int i = 0; i < count(); i++) {
        initStyleOption(&opt, i);

        auto iconRect = QRect();
        iconRect.setSize(opt.iconSize);
        iconRect.moveCenter(opt.rect.center());
        auto closeRect = iconRect;
        iconRect.moveLeft(opt.rect.left() + 15);
        closeRect.moveRight(opt.rect.right() - 15);
        auto textRect = opt.rect;
        textRect.setLeft(iconRect.right() + 5);
        textRect.setRight(closeRect.left() - 5);

        // draw background
        painter.drawControl(QStyle::CE_TabBarTabShape, opt);

        // draw icon
        opt.icon.paint(&painter, iconRect, Qt::AlignCenter);

        // draw text
        painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, opt.text);
    }
}
