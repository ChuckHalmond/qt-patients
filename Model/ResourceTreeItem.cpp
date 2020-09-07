#include "ResourceTreeItem.h"

ResourceTreeItem::ResourceTreeItem(const QVector<QVariant> &data, ResourceTreeItem *parent)
{
    parentItem = parent;
    itemData = data;
}

ResourceTreeItem::~ResourceTreeItem()
{
    qDeleteAll(childItems);
}

ResourceTreeItem *ResourceTreeItem::parent()
{
    return parentItem;
}

ResourceTreeItem *ResourceTreeItem::child(int number)
{
    return childItems.value(number);
}

int ResourceTreeItem::childCount() const
{
    return childItems.count();
}

int ResourceTreeItem::childNumber() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<ResourceTreeItem*>(this));

    return 0;
}

int ResourceTreeItem::columnCount() const
{
    return itemData.count();
}

QVariant ResourceTreeItem::data(int column) const
{
    return itemData.value(column);
}

bool ResourceTreeItem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= itemData.size())
        return false;

    itemData[column] = value;
    return true;
}

bool ResourceTreeItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QVector<QVariant> data(columns);
        ResourceTreeItem *item = new ResourceTreeItem(data, this);
        childItems.insert(position, item);
    }

    return true;
}

bool ResourceTreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}

bool ResourceTreeItem::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.remove(position);

    foreach (ResourceTreeItem *child, childItems)
        child->removeColumns(position, columns);

    return true;
}


bool ResourceTreeItem::insertColumns(int position, int columns)
{
    if (position < 0 || position > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.insert(position, QVariant());

    foreach (ResourceTreeItem *child, childItems)
        child->insertColumns(position, columns);

    return true;
}
