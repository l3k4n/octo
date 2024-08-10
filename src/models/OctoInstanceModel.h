#ifndef MODEL_OCTO_INSTANCE_H
#define MODEL_OCTO_INSTANCE_H

#include <QAbstractListModel>
#include <QIcon>

namespace octo::models {

struct BasicTab {
    QString title;
    QString url;
    QIcon favicon;
};

class OctoInstanceModel : public QAbstractListModel {
    Q_OBJECT;

public:
    enum Roles {
        TitleRole = Qt::UserRole + 1,
        UrlRole,
        FaviconRole,
        HasPrevPageRole,
        HasNextPageRole
    };
    explicit OctoInstanceModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QVector<BasicTab> m_tabs;
};

}  // namespace octo::models

#endif  // !MODEL_OCTO_INSTANCE_H
