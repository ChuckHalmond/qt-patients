#include "ResourceTypeDAO.h"
#include "Util/DBManager.h"

#include <QSqlQuery>
#include <QVariant>

ResourceTypeDAO::ResourceTypeDAO()
{
}

ResourceTypeDAO::~ResourceTypeDAO()
{

}

ResourceType ResourceTypeDAO::get(int id)
{
    DBManager::openDB();

    QSqlQuery query;

    query.prepare(
        "SELECT "
            "Id, Label "
        "FROM "
             "TType "
        "WHERE "
             "Id = :Id"
    );

    query.bindValue(":Id", id);

    query.exec();

    ResourceType resourceType;

    if (query.first()) {
        int id = query.value(0).toInt();
        QString label = query.value(1).toString();

        resourceType.setId(id);
        resourceType.setLabel(label);
    }

    DBManager::closeDB();

    return resourceType;
}

ResourceType ResourceTypeDAO::getByLabel(QString label)
{
    DBManager::openDB();

    QSqlQuery query;

    query.prepare(
        "SELECT "
            "Id, Label "
        "FROM "
             "TType "
        "WHERE "
             "Label = :Label"
    );

    query.bindValue(":Label", label);

    query.exec();

    ResourceType resourceType;

    if (query.first()) {
        int id = query.value(0).toInt();
        QString label = query.value(1).toString();

        resourceType.setId(id);
        resourceType.setLabel(label);
    }

    DBManager::closeDB();

    return resourceType;
}

QList<ResourceType> ResourceTypeDAO::getList()
{
    DBManager::openDB();

    QSqlQuery query;

    query.prepare(
        "SELECT "
            "Id, Label "
        "FROM "
             "TType"
    );

    query.exec();

    QList<ResourceType> resourceTypesList;
    ResourceType resourceType;

    while (query.next()) {
        int id = query.value(0).toInt();
        QString label = query.value(1).toString();

        resourceType.setId(id);
        resourceType.setLabel(label);

        resourceTypesList.append(resourceType);
    }

    DBManager::closeDB();

    return resourceTypesList;
}

QList<QString> ResourceTypeDAO::getLabelsList()
{
    DBManager::openDB();

    QSqlQuery query;

    query.prepare(
        "SELECT "
            "Label "
        "FROM "
             "TType"
    );

    query.exec();

    QList<QString> labelsList;

    while (query.next()) {
        QString label = query.value(0).toString();

        labelsList.append(label);
    }

    DBManager::closeDB();

    return labelsList;
}
