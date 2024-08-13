#ifndef GUI_TAB_PAGE_H
#define GUI_TAB_PAGE_H

#include <QLineEdit>
#include <QPersistentModelIndex>
#include <QPushButton>
#include <QWidget>

namespace octo::gui {

class TabPage : public QWidget {
    Q_OBJECT;

public:
    TabPage(const QPersistentModelIndex modelIndex, QWidget *parent = nullptr);

private:
    const QPersistentModelIndex modelIndex;
    QPushButton *navBackBtn;
    QPushButton *navNextBtn;
    QPushButton *navRefreshBtn;
    QLineEdit *addressBar;
};

}  // namespace octo::gui

#endif  // !GUI_TAB_PAGE_H
