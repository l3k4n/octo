#ifndef GUI_BROWSER_WINDOW_H
#define GUI_BROWSER_WINDOW_H

#include <QLineEdit>
#include <QPersistentModelIndex>
#include <QPushButton>
#include <QWidget>

namespace octo::gui {

class BrowserWindow : public QWidget {
    Q_OBJECT;

public:
    BrowserWindow(const QPersistentModelIndex model_index, QWidget *parent = nullptr);

private:
    const QPersistentModelIndex model_index;
    QPushButton *navBackBtn;
    QPushButton *navNextBtn;
    QPushButton *navRefreshBtn;
    QLineEdit *addressBar;
};

}  // namespace octo::gui

#endif  // !GUI_BROWSER_WINDOW_H
