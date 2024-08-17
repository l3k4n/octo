#ifndef CORE_TAB_H
#define CORE_TAB_H

#include <QIcon>
#include <QObject>
#include <memory>

namespace octo::core {

class Window;

class Tab : public QObject {
    Q_OBJECT;

    friend Window;

    Tab(Window* parent, int position);
    Tab(const QString& url, int position, Window* parent);
    void setPosition(int position);

public:
    const QString& title() const;
    const QString& url() const;
    const QIcon favicon() const;
    int position() const;

public slots:
    void navigate(const QString& url);

signals:
    void urlChanged(const QString& url);
    void titleChanged(const QString& title);

private:
    struct PageData {
        QString title;
        QString url;
        QIcon favicon;
    };

    int pos;
    std::unique_ptr<PageData> newPage();
    std::unique_ptr<PageData> pageData;
};

}  // namespace octo::core

#endif  // !CORE_TAB_H
