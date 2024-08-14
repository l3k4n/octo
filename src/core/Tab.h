#ifndef CORE_TAB_H
#define CORE_TAB_H

#include <QIcon>
#include <QObject>

namespace octo::core {

class Tab : protected QObject {
    Tab();
    Tab(const QString& url);
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

    std::unique_ptr<Tab::PageData> newPage();
    std::unique_ptr<PageData> pageData;
};

}  // namespace octo::core

#endif  // !CORE_TAB_H
