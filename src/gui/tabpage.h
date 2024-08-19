#ifndef GUI_TAB_PAGE_H
#define GUI_TAB_PAGE_H

#include <QWidget>

#include "core/Tab.h"

class TabPage : public QWidget {
    Q_OBJECT;

public:
    TabPage(Core::Tab &tab, QWidget *parent = nullptr);

private:
    Core::Tab &tab;
};

#endif  // !GUI_TAB_PAGE_H
