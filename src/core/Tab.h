#ifndef CORE_TAB_H
#define CORE_TAB_H

#include <QIcon>
#include <QObject>
#include <memory>

namespace octo::core {

class Tab : public QObject {
    Q_OBJECT;

    Tab(QObject* parent);
    Tab(const QString& url, QObject* parent);
    friend class Window;

public:
    const QString& title() const;
    const QString& url() const;
    const QIcon favicon() const;

private:
    struct PageData {
        QString title;
        QString url;
        QIcon favicon;
    };

    std::unique_ptr<PageData> newPage();
    std::unique_ptr<PageData> pageData;
};

}  // namespace octo::core

#endif  // !CORE_TAB_H
