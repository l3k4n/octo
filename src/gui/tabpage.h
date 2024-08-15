#ifndef GUI_TAB_PAGE_H
#define GUI_TAB_PAGE_H

#include <QLineEdit>
#include <QPushButton>
#include <QSize>
#include <QWidget>

#include "Tab.h"
#include "navbarbutton.h"

namespace octo::gui {

class TabPage : public QWidget {
    Q_OBJECT;

public:
    TabPage(const core::Tab &tab, QWidget *parent = nullptr);

private:
    void setupNavBarWidgets();

private:
    const core::Tab &tab;
    QSize btnSize = QSize(30, 30);
    QSize iconSize = QSize(15, 15);
    int addressBarHeight = 30;
    NavBarButton *navBackBtn;
    NavBarButton *navNextBtn;
    NavBarButton *navRefreshBtn;
    QLineEdit *addressBar;
};

}  // namespace octo::gui

#endif  // !GUI_TAB_PAGE_H
