#include <qboxlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qtmetamacros.h>
#include <qwidget.h>

namespace Octo::Widgets {

class Navbar : public QWidget {
    Q_OBJECT;

public:
    Navbar(QWidget *parent = nullptr);

private:
    QLineEdit *url_input;
    QBoxLayout *navbar_layout;

protected:
    void paintEvent(QPaintEvent *event) override;
};

}  // namespace Octo::Widgets
