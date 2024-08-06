#ifndef GUI_TAB_BAR_H
#define GUI_TAB_BAR_H

#include <QListView>
#include <QStyledItemDelegate>
#include <QWidget>

namespace octo::gui {

class TabBarView : public QListView {
    Q_OBJECT;

public:
    TabBarView(QWidget *parent = nullptr);
};

}  // namespace octo::gui

#endif  // !GUI_TAB_BAR_H
