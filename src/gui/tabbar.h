#ifndef GUI_TAB_BAR_H
#define GUI_TAB_BAR_H

#include <QPaintEvent>
#include <QTabBar>
#include <QWidget>

class TabBar : public QTabBar {
    Q_OBJECT;

public:
    TabBar(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *) override;
};

#endif  // !GUI_TAB_BAR_H
