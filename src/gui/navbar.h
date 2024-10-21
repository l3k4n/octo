#ifndef GUI_NAV_BAR_H
#define GUI_NAV_BAR_H

#include <QLineEdit>
#include <QWidget>

#include "gui/navbarbutton.h"

class NavBar : public QWidget {
    Q_OBJECT;

public:
    NavBar(QWidget* parent = nullptr);

public slots:
    void setUrl(const QString& url);
    void setBackButtonEnabled(bool enabled);
    void setNextButtonEnabled(bool enabled);

signals:
    void urlSubmitted(const QString& url);
    void backClicked();
    void nextClicked();
    void refreshClicked();

private:
    void paintEvent(QPaintEvent* event) override;

private:
    QSize btnSize = QSize(30, 30);
    QSize iconSize = QSize(15, 15);
    int addressBarHeight = 30;
    NavBarButton* navBackBtn;
    NavBarButton* navNextBtn;
    NavBarButton* navRefreshBtn;
    QLineEdit* addressBar;
};

#endif  // !GUI_NAV_BAR_H
