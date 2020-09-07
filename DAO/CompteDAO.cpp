#include "UserDAO.h"

#include <Util/DBManager.h>

#include <QSqlQuery>
#include <QVariant>

CompteDAO::CompteDAO() : resourceDAO(new ResourceDAO())
{

}

CompteDAO::~CompteDAO()
{
}

bool CompteDAO::checkLogin(QString login, QString mdp)
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
    query.bindValue(":MdP", mdp);

    query.exec();

    DBManager::closeDB();
    return query.first();
}

Compte CompteDAO::get(int id)
{
    DBManager::openDB();


    QSqlQuery query;

    query.prepare(
        "SELECT "
            "Id, IdResource, Login, MdP "
        "FROM "
             "TConsult "
        "WHERE "
             "Id = :Id"
    );

    query.bindValue(":Id", id);

    query.exec();

    Compte compte;

    if (query.first()) {
        int id = query.value(0).toInt();
        Resource resource = resourceDAO->get(query.value(1).toInt()) ;
        QString login = query.value(2).toString();
        QString mdp = query.value(3).toString();

        compte.setId(id);
        compte.setResource(resource);
        compte.setLogin(login);
        compte.setMdp(mdp);
    }

    DBManager::closeDB();

    return compte;
}

QList<Compte> CompteDAO::getList()
{
    DBManager::openDB();

    QSqlQuery query;
    query.exec(
            "SELECT "
                "Id, IdResource, Login, MdP "
            "FROM "
                 "TConsult "
    );

    QList<Compte> comptesList;
    Compte compte;

    while (query.next()) {
        int id = query.value(0).toInt();
        Resource resource = resourceDAO->get(query.value(1).toInt()) ;
        QString login = query.value(2).toString();
        QString mdp = query.value(3).toString();

        compte.setId(id);
        compte.setResource(resource);
        compte.setLogin(login);
        compte.setMdp(mdp);

        comptesList.append(compte);
    }

    DBManager::closeDB();

    return comptesList;
}

bool CompteDAO::add(Compte compte)
{
    DBManager::openDB();

    QSqlQuery query;
    query.prepare(
        "INSERT INTO "
            "TCompte "
        "VALUES("
            ":Id, :IdResource, :Login, :Mdp "
        ")"
    );

    query.bindValue(":Id", compte.getId());
    query.bindValue(":IdResource", compte.getResource().getId());
    query.bindValue(":Login", compte.getLogin());
    query.bindValue(":Mdp", compte.getMdp());

    int result = query.exec();

    DBManager::closeDB();

    return result;
}

bool CompteDAO::remove(int id)
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

bool CompteDAO::update(Compte compte)
{
    DBManager::openDB();

    QSqlQuery query;
    query.prepare(
        "UPDATE "
            "TCompte "
        "SET "
            "IdResource = :IdResource, Login = :Login, MdP = :MdP "
        "WHERE "
            "Id = :Id"
    );

    query.bindValue(":Id", compte.getId());
    query.bindValue(":IdResource", compte.getResource().getId());
    query.bindValue(":Login", compte.getLogin());
    query.bindValue(":MdP", compte.getMdp());

    int result = query.exec();

    DBManager::closeDB();

    return result;
}
