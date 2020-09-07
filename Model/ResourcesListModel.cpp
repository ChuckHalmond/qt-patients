#include "ResourcesListModel.h"

#include <iostream>

ResourcesListModel::ResourcesListModel(QObject *parent) :
    QAbstractListModel(parent),
    resources(QList<Resource>())
{
}

ResourcesListModel::~ResourcesListModel()
{
}

int ResourcesListModel::rowCount(const QModelIndex &/*parent*/) const
{
    return resources.size();
}

QVariant ResourcesListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= resources.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        Resource resource = resources.at(index.row());

        if (index.column() == 0)
            return QStringLiteral("%1\t%2\t%3").arg(resource.getId()).arg(resource.getName()).arg(resource.getFirstname());
    }

    return QVariant();
}

QVariant ResourcesListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Resource");
        }
    }
    return QVariant();
}

void ResourcesListModel::setRows(QList<Resource> resources)
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    endRemoveRows();

    this->resources.clear();

    beginInsertRows(QModelIndex(), 0, resources.size());

    for (QList<Resource>::iterator it = resources.begin(); it != resources.end(); ++it)
    {
        this->resources.append(*it);
    }

    endInsertRows();
}

void ResourcesListModel::removeRows()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());

    this->resources.clear();

    endRemoveRows();
}

QList<Resource> ResourcesListModel::getResourcesFromIndexes(QModelIndexList indexList)
{
    QList<Resource> resources;

    for (int i = 0; i < indexList.size(); i++)
    {
        resources.append(this->resources.at(indexList.at(i).row()));
    }

    return resources;
}
