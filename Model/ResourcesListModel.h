#ifndef RESOURCESLISTMODEL_H
#define RESOURCESLISTMODEL_H

#include "Model/Resource.h"

#include <QAbstractListModel>

class ResourcesListModel : public QAbstractListModel
{
    Q_OBJECT

    private:
        QList<Resource> resources;

    public:
        ResourcesListModel(QObject *parent = 0);
        ~ResourcesListModel();

        int rowCount(const QModelIndex &parent = QModelIndex()) const;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
        QVariant headerData(int section, Qt::Orientation orientation, int role) const;

        void setRows(QList<Resource> resources);
        void removeRows();
        QList<Resource> getResourcesFromIndexes(QModelIndexList indexList);
};

#endif // RESOURCESLISTMODEL_H
