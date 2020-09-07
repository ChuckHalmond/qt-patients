#include "ResourceDAO.h"
#include "Util/DBManager.h"

#include <QSqlQuery>
#include <QVariant>

ResourceDAO::ResourceDAO()
{
}

ResourceDAO::~ResourceDAO()
{
}

bool ResourceDAO::contains(int id)
{
    DBManager::openDB();

    QSqlQuery query;

    query.prepare(
        "SELECT "
            "1 "
        "FROM "
             "TRessource "
        "WHERE "
             "Id = :Id"
    );

    query.bindValue(":Id", id);

    query.exec();

    return query.first();
}

Resource ResourceDAO::get(int id)
{
    DBManager::openDB();

    QSqlQuery query;

    query.prepare(
        "SELECT "
            "Id, Nom, Prenom, IdType "
        "FROM "
             "TRessource "
        "WHERE "
             "Id = :Id"
    );

    query.bindValue(":Id", id);

    query.exec();

    Resource resource;

    if (query.first()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString firstname = query.value(2).toString();
        int typeId = query.value(3).toInt();

        resource.setId(id);
        resource.setName(name);
        resource.setFirstname(firstname);
        resource.setType(resourceTypeDAO.get(typeId));
    }

    DBManager::closeDB();

    return resource;
}

QList<Resource> ResourceDAO::getList()
{
    DBManager::openDB();

    QSqlQuery query;
    query.exec(
        "SELECT "
            "Id, Nom, Prenom, IdType "
        "FROM "
             "TRessource"
    );

    QList<Resource> resourcesList;
    Resource resource;

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString firstname = query.value(2).toString();
        int typeId = query.value(3).toInt();

        resource.setId(id);
        resource.setName(name);
        resource.setFirstname(firstname);
        resource.setType(resourceTypeDAO.get(typeId));

        resourcesList.append(resource);
    }

    DBManager::closeDB();

    return resourcesList;
}

bool ResourceDAO::add(Resource resource)
{
    DBManager::openDB();

    QSqlQuery query;
    query.prepare(
        "INSERT INTO "
            "TRessource "
        "VALUES("
            ":Id, :Nom, :Prenom, :IdType "
        ")"
    );

    query.bindValue(":Id", resource.getId());
    query.bindValue(":Nom", resource.getName());
    query.bindValue(":Prenom", resource.getFirstname());
    query.bindValue(":IdType", resource.getType().getId());

    int result = query.exec();

    DBManager::closeDB();

    return result;
}

bool ResourceDAO::remove(int id)
{
    DBManager::openDB();

    QSqlQuery query;

    query.prepare(
        "DELETE FROM "
            "TRessource "
        "WHERE "
            "Id = :Id"
    );

    query.bindValue(":Id", id);

    bool result = query.exec();

    DBManager::closeDB();

    return result;
}

bool ResourceDAO::update(Resource resource)
{
    DBManager::openDB();

    QSqlQuery query;
    query.prepare(
        "UPDATE "
            "TRessource "
        "SET "
            "Nom = :Nom, Prenom = :Prenom, IdType = :IdType "
        "WHERE "
            "Id = :Id"
    );

    query.bindValue(":Id", resource.getId());
    query.bindValue(":Nom", resource.getName());
    query.bindValue(":Prenom", resource.getFirstname());
    query.bindValue(":IdType", resource.getType().getId());

    int result = query.exec();

    DBManager::closeDB();

    return result;
}

int ResourceDAO::getNextId()
{
    DBManager::openDB();

    QSqlQuery query;

    query.exec(
        "SELECT "
            "MAX(Id) "
        "FROM "
             "TRessource"
    );

    int nextId;

    if (query.first()) {
        nextId = query.value(0).toInt() + 1;
    }
    else {
        nextId = 1;
    }

    DBManager::closeDB();

    return nextId;
}

QList<Resource> ResourceDAO::getListFromTypeId(int typeId)
{
    DBManager::openDB();

    QSqlQuery query;

    query.prepare(
        "SELECT "
            "Id, Nom, Prenom, IdType "
        "FROM "
             "TRessource "
        "WHERE "
             "IdType = :IdType"
    );

    query.bindValue(":IdType", typeId);

    query.exec();

    QList<Resource> resourcesList;
    Resource resource;

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString firstname = query.value(2).toString();
        int typeId = query.value(3).toInt();

        resource.setId(id);
        resource.setName(name);
        resource.setFirstname(firstname);
        resource.setType(resourceTypeDAO.get(typeId));

        resourcesList.append(resource);
    }

    DBManager::closeDB();

    return resourcesList;
}
