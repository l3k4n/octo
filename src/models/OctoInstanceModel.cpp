#include "OctoInstanceModel.h"

#include <QAbstractListModel>
#include <QIcon>
#include <QVariant>
#include <QObject>

using namespace octo::models;

OctoInstanceModel::OctoInstanceModel(QObject *parent) : QAbstractListModel(parent) {
    m_tabs.emplace_back(BasicTab{.title = "New Tab"});
}

int OctoInstanceModel::rowCount(const QModelIndex &parent) const { return m_tabs.size(); }

QVariant OctoInstanceModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_tabs.size()) return QVariant();
    const BasicTab &tab = m_tabs[index.row()];

    switch (role) {
        case Roles::TitleRole:
            return tab.title;
        case Roles::UrlRole:
            return tab.url;
        case Roles::FaviconRole:
            return tab.favicon;
        case Roles::HasPrevPageRole:
            return QVariant(false);
        case Roles::HasNextPageRole:
            return QVariant(false);
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> OctoInstanceModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[Roles::TitleRole] = "title";
    roles[Roles::UrlRole] = "url";
    roles[Roles::FaviconRole] = "favicon";
    roles[Roles::HasPrevPageRole] = "hasPreviousPage";
    roles[Roles::HasPrevPageRole] = "hasNextPage";

    return roles;
}
