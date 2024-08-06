#include <QListView>
#include <QStyledItemDelegate>
#include <QWidget>

namespace octo::gui {

class TabBarView : public QListView {
    Q_OBJECT;

public:
    TabBarView(QWidget *parent = nullptr);
};

}  // namespace octo::gui
