#ifndef RESOURCETREEMODEL_H
#define RESOURCETREEMODEL_H

#include "Model/ResourceTreeItem.h"
#include "Model/Resource.h"
#include "Model/ResourceType.h"
#include <QAbstractItemModel>
#include <QVariant>

class ResourceTreeModel : public QAbstractItemModel
{
    Q_OBJECT

    private:
        ResourceTreeItem *rootItem;
        void setupModelData(const QStringList &lines, ResourceTreeItem *parent);

    public:
        ResourceTreeModel(const QStringList &headers, const QString &data, QObject *parent = 0);
        ~ResourceTreeModel();

        QVariant data(const QModelIndex &index, int role) const;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

        QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
        QModelIndex parent(const QModelIndex &index) const;

        int rowCount(const QModelIndex &parent = QModelIndex()) const;
        int columnCount(const QModelIndex &parent = QModelIndex()) const;
        Qt::ItemFlags flags(const QModelIndex &index) const;
        bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole);
        bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::DisplayRole);

        bool insertColumns(int position, int columns, const QModelIndex &parent = QModelIndex());
        bool removeColumns(int position, int columns,  const QModelIndex &parent = QModelIndex());
        bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex());
        bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex());

        ResourceTreeItem *getItem(const QModelIndex &index) const;
        ResourceTreeItem *getRootItem();
    };

#endif // RESOURCETREEMODEL_H
