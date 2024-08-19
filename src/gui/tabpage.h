#ifndef GUI_TAB_PAGE_H
#define GUI_TAB_PAGE_H

#include <QWidget>

class TabPage : public QWidget {
    Q_OBJECT;

public:
    TabPage(QWidget *parent = nullptr);
};

#endif  // !GUI_TAB_PAGE_H
