#include "tabbutton.h"

#include <QPainter>

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

    // prevent mouseover state when if tab is selected
    if (opt.state & QStyle::State_Selected) {
        opt.state &= ~QStyle::State_MouseOver;
    }

    // Draw background
    QStyle *style = option.widget->style();
    style->drawPrimitive(QStyle::PE_PanelItemViewItem, &opt, painter, opt.widget);

    // Draw icon
    QRect icon_rect(
        opt.rect.adjusted(GAP, (opt.rect.height() - opt.decorationSize.height()) / 2, 0, 0));
    QIcon icon = qvariant_cast<QIcon>(index.data(Qt::DecorationRole));
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
