#ifndef GUI_TAB_PAGE_H
#define GUI_TAB_PAGE_H

#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

#include "Tab.h"

namespace octo::gui {

class TabPage : public QWidget {
    Q_OBJECT;

public:
    TabPage(const core::Tab &tab, QWidget *parent = nullptr);

private:
    const core::Tab &tab;
    QPushButton *navBackBtn;
    QPushButton *navNextBtn;
    QPushButton *navRefreshBtn;
    QLineEdit *addressBar;
};

}  // namespace octo::gui

#endif  // !GUI_TAB_PAGE_H
