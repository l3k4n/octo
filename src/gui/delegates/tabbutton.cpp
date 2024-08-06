#include "tabbutton.h"

#include <QPainter>
#include <QPainterPath>

using namespace octo::gui;

const int CORNER_RADIUS = 5;
const int GAP = 5;

QSize TabBarButtonDelegate::sizeHint(const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const {
    return QSize(180, 30);
}

void TabBarButtonDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const {
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);

    // Draw background
    if (opt.state & QStyle::State_Selected) {
        QPainterPath path;
        QColor cc("#00FFFFFF");  // (ARGB) translucent white
        cc.setAlphaF(0.1);
        path.addRoundedRect(option.rect.adjusted(0, 0, 0, 0), CORNER_RADIUS, CORNER_RADIUS);
        painter->setRenderHint(QPainter::Antialiasing);
        painter->fillPath(path, QBrush(cc));
    }

    // Draw icon
    QIcon icon = qvariant_cast<QIcon>(index.data(Qt::DecorationRole));
    QRect icon_rect(
        opt.rect.adjusted(GAP, (opt.rect.height() - opt.decorationSize.height()) / 2, 0, 0));
    icon_rect.setSize(opt.decorationSize);
    icon.paint(painter, icon_rect, Qt::AlignLeft | Qt::AlignVCenter);

    // Draw text
    int text_offset = (opt.rect.height() - opt.fontMetrics.height()) / 2;
    QRect text_rect =
        opt.rect.adjusted(opt.decorationSize.width() + (2 * GAP), text_offset, -GAP, 0);
    text_rect.setHeight(opt.fontMetrics.height());
    painter->setPen("#ffffff");
    painter->drawText(text_rect, opt.displayAlignment, index.data(Qt::DisplayRole).toString());
}
