#ifndef GUI_TAB_PAGE_H
#define GUI_TAB_PAGE_H

#include <QLineEdit>
#include <QPushButton>
#include <QSize>
#include <QWidget>

#include "core/Tab.h"
#include "gui/navbarbutton.h"

class TabPage : public QWidget {
    Q_OBJECT;

public:
    TabPage(Core::Tab &tab, QWidget *parent = nullptr);

private:
    void setupNavBarWidgets();
    void setupPageLayout();

private:
    Core::Tab &tab;
    QSize btnSize = QSize(30, 30);
    QSize iconSize = QSize(15, 15);
    int addressBarHeight = 30;
    NavBarButton *navBackBtn;
    NavBarButton *navNextBtn;
    NavBarButton *navRefreshBtn;
    QLineEdit *addressBar;
};

#endif  // !GUI_TAB_PAGE_H
