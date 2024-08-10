#include "tabbutton.h"

#include <QPainter>

#include "OctoInstanceModel.h"

using namespace octo;
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
    QRect iconRect(
        opt.rect.adjusted(GAP, (opt.rect.height() - opt.decorationSize.height()) / 2, 0, 0));
    QIcon icon = qvariant_cast<QIcon>(index.data(models::OctoInstanceModel::FaviconRole));
    iconRect.setSize(opt.decorationSize);
    icon.paint(painter, iconRect, Qt::AlignLeft | Qt::AlignVCenter);

    // Draw text
    int textOffset = (opt.rect.height() - opt.fontMetrics.height()) / 2;
    QRect textRect = opt.rect.adjusted(opt.decorationSize.width() + (2 * GAP), textOffset, -GAP, 0);
    textRect.setHeight(opt.fontMetrics.height());
    painter->setPen("#ffffff");
    painter->drawText(textRect, opt.displayAlignment,
                      index.data(models::OctoInstanceModel::TitleRole).toString());
}
