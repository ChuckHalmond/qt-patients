#include "ResourceTreeModel.h"

ResourceTreeModel::ResourceTreeModel(const QStringList &headers, const QString &data, QObject *parent)
    : QAbstractItemModel(parent)
{
    QVector<QVariant> rootData;
    foreach (QString header, headers)
        rootData << header;

    rootItem = new ResourceTreeItem(rootData);
    setupModelData(data.split(QString("\n")), rootItem);
}

ResourceTreeModel::~ResourceTreeModel()
{
    delete rootItem;
}

QVariant ResourceTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::DisplayRole)
        return QVariant();

    ResourceTreeItem *item = getItem(index);

    return item->data(index.column());
}

QVariant ResourceTreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

bool ResourceTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::DisplayRole)
        return false;

    ResourceTreeItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    QVector<int> roles;
    roles.append(role);
    if (result)
        emit dataChanged(index, index, roles);

    return result;
}

bool ResourceTreeModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return false;

    bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

bool ResourceTreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginInsertColumns(parent, position, position + columns - 1);
    success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool ResourceTreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    ResourceTreeItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    endInsertRows();

    return success;
}

bool ResourceTreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginRemoveColumns(parent, position, position + columns - 1);
    success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool ResourceTreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    ResourceTreeItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

ResourceTreeItem *ResourceTreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        ResourceTreeItem *item = static_cast<ResourceTreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}

int ResourceTreeModel::rowCount(const QModelIndex &parent) const
{
    ResourceTreeItem *parentItem = getItem(parent);

    return parentItem->childCount();
}

int ResourceTreeModel::columnCount(const QModelIndex & /* parent */) const
{
    return rootItem->columnCount();
}

Qt::ItemFlags ResourceTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

QModelIndex ResourceTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    ResourceTreeItem *parentItem = getItem(parent);
    ResourceTreeItem *childItem = parentItem->child(row);

    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex ResourceTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    ResourceTreeItem *childItem = getItem(index);
    ResourceTreeItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}

void ResourceTreeModel::setupModelData(const QStringList &lines, ResourceTreeItem *parent)
{
    QList<ResourceTreeItem*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

    while (number < lines.count()) {
        int position = 0;
        while (position < lines[number].length()) {
            if (lines[number].at(position) != ' ')
                break;
            ++position;
        }

        QString lineData = lines[number].mid(position).trimmed();

        if (!lineData.isEmpty()) {
            // Read the column data from the rest of the line.
            QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);
            QVector<QVariant> columnData;
            for (int column = 0; column < columnStrings.count(); ++column)
                columnData << columnStrings[column];

            if (position > indentations.last()) {
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.

                if (parents.last()->childCount() > 0) {
                    parents << parents.last()->child(parents.last()->childCount()-1);
                    indentations << position;
                }
            } else {
                while (position < indentations.last() && parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            // Append a new item to the current parent's list of children.
            ResourceTreeItem *parent = parents.last();
            parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
            for (int column = 0; column < columnData.size(); ++column)
                parent->child(parent->childCount() - 1)->setData(column, columnData[column]);
        }

        ++number;
    }
}

ResourceTreeItem *ResourceTreeModel::getRootItem()
{
    return rootItem;
}
