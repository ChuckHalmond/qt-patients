#include "UserDAO.h"

#include <Util/DBManager.h>

#include <QSqlQuery>
#include <QVariant>

#include <iostream>

UserDAO::UserDAO() :
    resourceDAO(new ResourceDAO())
{

}

UserDAO::~UserDAO()
{
    delete resourceDAO;
    resourceDAO = NULL;
}

bool UserDAO::exists(QString login, QString password)
{
    DBManager::openDB();

    QSqlQuery query;

    query.prepare(
        "SELECT "
            "1 "
        "FROM "
             "TCompte "
        "WHERE "
             "Login = :Login AND MdP = :MdP"
    );

    query.bindValue(":Login", login);
    query.bindValue(":MdP", password);

    query.exec();

    DBManager::closeDB();

    return query.first();
}

User UserDAO::get(int id)
{
    DBManager::openDB();


    QSqlQuery query;

    query.prepare(
        "SELECT "
            "Id, IdRessource, Login, MdP "
        "FROM "
             "TConsult "
        "WHERE "
             "Id = :Id"
    );

    query.bindValue(":Id", id);

    query.exec();

    User user;

    if (query.first()) {
        int id = query.value(0).toInt();
        Resource resource = resourceDAO->get(query.value(1).toInt()) ;
        QString login = query.value(2).toString();
        QString password = query.value(3).toString();

        user.setId(id);
        user.setResource(resource);
        user.setLogin(login);
        user.setPassword(password);
    }

    DBManager::closeDB();

    return user;
}

QList<User> UserDAO::getList()
{
    DBManager::openDB();

    QSqlQuery query;
    query.exec(
            "SELECT "
                "Id, IdRessource, Login, MdP "
            "FROM "
                 "TConsult "
    );

    QList<User> usersList;
    User user;

    while (query.next()) {
        int id = query.value(0).toInt();
        Resource resource = resourceDAO->get(query.value(1).toInt()) ;
        QString login = query.value(2).toString();
        QString password = query.value(3).toString();

        user.setId(id);
        user.setResource(resource);
        user.setLogin(login);
        user.setPassword(password);

        usersList.append(user);
    }

    DBManager::closeDB();

    return usersList;
}

bool UserDAO::add(User user)
{
    DBManager::openDB();

    QSqlQuery query;

    query.prepare(
        "INSERT INTO "
            "TCompte "
        "VALUES( "
            ":Id, :IdRessource, :Login, :Mdp "
        ")"
    );

    query.bindValue(":Id", user.getId());
    query.bindValue(":IdRessource", user.getResource().getId());
    query.bindValue(":Login", user.getLogin());
    query.bindValue(":Mdp", user.getPassword());

    int result = query.exec();

    DBManager::closeDB();

    return result;
}

bool UserDAO::remove(int id)
{
    DBManager::openDB();

    QSqlQuery query;

    query.prepare(
        "DELETE FROM "
            "TCompte "
        "WHERE "
            "Id = :Id"
    );

    query.bindValue(":Id", id);

    bool result = query.exec();

    DBManager::closeDB();

    return result;
}

bool UserDAO::update(User user)
{
    DBManager::openDB();

    QSqlQuery query;

    query.prepare(
        "UPDATE "
            "TCompte "
        "SET "
            "IdRessource = :IdRessource, Login = :Login, MdP = :MdP "
        "WHERE "
            "Id = :Id"
    );

    query.bindValue(":Id", user.getId());
    query.bindValue(":IdRessource", user.getResource().getId());
    query.bindValue(":Login", user.getLogin());
    query.bindValue(":MdP", user.getPassword());

    int result = query.exec();

    DBManager::closeDB();

    return result;
}

User UserDAO::getFromResourceId(int resourceId)
{
    DBManager::openDB();

    QSqlQuery query;

    query.prepare(
        "SELECT "
            "Id, IdRessource, Login, MdP "
        "FROM "
             "TCompte "
        "WHERE "
             "IdRessource = :IdRessource"
    );

    query.bindValue(":IdRessource", resourceId);

    query.exec();

    User user;

    if (query.first()) {
        int id = query.value(0).toInt();
        Resource resource = resourceDAO->get(query.value(1).toInt()) ;
        QString login = query.value(2).toString();
        QString password = query.value(3).toString();

        user.setId(id);
        user.setResource(resource);
        user.setLogin(login);
        user.setPassword(password);
    }
    else {
        // TODO: Do the same for every DAO
        user.setId(0);
    }

    DBManager::closeDB();

    return user;
}

int UserDAO::getNextId()
{
    DBManager::openDB();

    QSqlQuery query;

    query.exec(
        "SELECT "
            "MAX(Id) "
        "FROM "
             "TCompte"
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
