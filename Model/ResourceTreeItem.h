#ifndef RESOURCETREEITEM_H
#define RESOURCETREEITEM_H

#include <QVariant>
#include <QVector>

class ResourceTreeItem
{
    private:
        QList<ResourceTreeItem*> childItems;
        QVector<QVariant> itemData;
        ResourceTreeItem *parentItem;

    public:
        explicit ResourceTreeItem(const QVector<QVariant> &data, ResourceTreeItem *parent = 0);
        ~ResourceTreeItem();

        ResourceTreeItem *child(int number);
        int childCount() const;
        int columnCount() const;
        QVariant data(int column) const;
        bool insertChildren(int position, int count, int columns);
        bool insertColumns(int position, int columns);
        ResourceTreeItem *parent();
        bool removeChildren(int position, int count);
        bool removeColumns(int position, int columns);
        int childNumber() const;
        bool setData(int column, const QVariant &value);
};

#endif // RESOURCETREEITEM_H
