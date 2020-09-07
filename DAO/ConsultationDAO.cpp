#include "ConsultationDAO.h"

#include "Util/DBManager.h"

#include <QSqlQuery>
#include <QVariant>


ConsultationDAO::ConsultationDAO()
{
}

QList<int> ConsultationDAO::getResourceIdsListFromPatientId(int id)
{
    DBManager::openDB();

    QSqlQuery query;

    query.prepare(
        "SELECT "
            "IdRessource "
        "FROM "
             "TConsult "
        "WHERE "
             "IdPatient = :IdPatient"
    );

    query.bindValue(":IdPatient", id);

    query.exec();

    QList<int> resourceIdsList;

    while (query.next()) {
        resourceIdsList.append(query.value(0).toInt());
    }

    DBManager::closeDB();

    return resourceIdsList;
}

bool ConsultationDAO::removeFromPatientId(int id)
{
    DBManager::openDB();

    QSqlQuery query;

    query.prepare(
        "DELETE FROM "
             "TConsult "
        "WHERE "
             "IdPatient = :IdPatient"
    );

    query.bindValue(":IdPatient", id);

    bool result = query.exec();

    DBManager::closeDB();

    return result;
}

bool ConsultationDAO::add(int resourceId, int patientId)
{
    DBManager::openDB();

    QSqlQuery query;

    query.prepare(
        "INSERT INTO "
            "TConsult "
        "VALUES("
            ":Id, :IdPatient, :IdResource "
        ")"
    );

    query.bindValue(":Id", getNextId());
    query.bindValue(":IdPatient", patientId);
    query.bindValue(":IdResource", resourceId);

    bool result = query.exec();

    DBManager::closeDB();

    return result;
}

int ConsultationDAO::getNextId()
{
    DBManager::openDB();

    QSqlQuery query;
    query.exec(
        "SELECT "
            "MAX(Id) "
        "FROM "
             "TConsult"
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
