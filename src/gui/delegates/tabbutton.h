#ifndef GUI_TAB_BUTTON_H
#define GUI_TAB_BUTTON_H

#include <QStyledItemDelegate>

namespace octo::gui {

class TabBarButtonDelegate : public QStyledItemDelegate {
    Q_OBJECT;

    using QStyledItemDelegate::QStyledItemDelegate;

public:
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
};

}  // namespace octo::gui

#endif  // !GUI_TAB_BUTTON_H
