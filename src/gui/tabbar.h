#ifndef GUI_TAB_BAR_H
#define GUI_TAB_BAR_H

#include <QPaintEvent>
#include <QTabBar>
#include <QWidget>

namespace octo::gui {

class TabBar : public QTabBar {
    Q_OBJECT;

public:
    TabBar(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *) override;
};

}  // namespace octo::gui

#endif  // !GUI_TAB_BAR_H
