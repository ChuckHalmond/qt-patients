#include "PatientDAO.h"
#include "Util/DBManager.h"
#include "Model/Resource.h"

#include <QSqlQuery>
#include <QVariant>

#include <iostream>

PatientDAO::PatientDAO() :
    resourceDAO(ResourceDAO()),
    consultationDAO(ConsultationDAO())
{
}

PatientDAO::~PatientDAO()
{
}

bool PatientDAO::contains(int id)
{
    DBManager::openDB();

    QSqlQuery query;

    query.prepare(
        "SELECT "
            "1 "
        "FROM "
             "TPatient "
        "WHERE "
             "Id = :Id"
    );

    query.bindValue(":Id", id);

    query.exec();

    DBManager::closeDB();
    return query.first();
}

Patient PatientDAO::get(int id)
{
    DBManager::openDB();


    QSqlQuery query;

    query.prepare(
        "SELECT "
            "Id, Nom, Prenom, Adresse, Ville, CP, Commentaire, Tel, DateConsultation, DureeConsultation, Priorite "
        "FROM "
             "TPatient "
        "WHERE "
             "Id = :Id"
    );

    query.bindValue(":Id", id);

    query.exec();

    Patient patient;

    if (query.first()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString firstname = query.value(2).toString();
        QString address = query.value(3).toString();
        QString city = query.value(4).toString();
        int zipCode = query.value(5).toInt();
        QString commentary = query.value(6).toString();
        int phoneNumber = query.value(7).toInt();
        QDate consultationDate = QDate::fromString(query.value(8).toString(), "yyyy-MM-dd");
        int consultationDuration = query.value(9).toInt();
        int priority = query.value(10).toInt();

        QList<Resource> resources;
        QList<int> resourceIds = consultationDAO.getResourceIdsListFromPatientId(id);
        for (int i = 0; i < resourceIds.size(); i++)
        {
            resources.append(resourceDAO.get(resourceIds.at(i)));
        }

        patient.setId(id);
        patient.setName(name);
        patient.setFirstname(firstname);
        patient.setConsultationDate(consultationDate);
        patient.setAddress(address);
        patient.setCity(city);
        patient.setZipCode(zipCode);
        patient.setConsultationDuration(consultationDuration);
        patient.setResources(resources);
        patient.setCommentary(commentary);
        patient.setPhoneNumber(phoneNumber);
        patient.setPriority(priority);
    }

    DBManager::closeDB();

    return patient;
}

QList<Patient> PatientDAO::getList()
{
    DBManager::openDB();

    QSqlQuery query;
    query.exec(
        "SELECT "
            "Id, Nom, Prenom, Adresse, Ville, CP, Commentaire, Tel, DateConsultation, DureeConsultation, Priorite "
        "FROM "
             "TPatient"
    );

    QList<Patient> patientsList;
    Patient patient;

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString firstname = query.value(2).toString();
        QString address = query.value(3).toString();
        QString city = query.value(4).toString();
        int zipCode = query.value(5).toInt();
        QString commentary = query.value(6).toString();
        int phoneNumber = query.value(7).toInt();
        QDate consultationDate = QDate::fromString(query.value(8).toString(), "yyyy-MM-dd");
        int consultationDuration = query.value(9).toInt();
        int priority = query.value(10).toInt();

        QList<Resource> resources;
        QList<int> resourceIds = consultationDAO.getResourceIdsListFromPatientId(id);
        for (int i = 0; i < resourceIds.size(); i++)
        {
            resources.append(resourceDAO.get(resourceIds.at(i)));
        }

        patient.setId(id);
        patient.setName(name);
        patient.setFirstname(firstname);
        patient.setConsultationDate(consultationDate);
        patient.setAddress(address);
        patient.setCity(city);
        patient.setZipCode(zipCode);
        patient.setConsultationDuration(consultationDuration);
        patient.setResources(resources);
        patient.setCommentary(commentary);
        patient.setPhoneNumber(phoneNumber);
        patient.setPriority(priority);

        patientsList.append(patient);
    }

    DBManager::closeDB();

    return patientsList;
}

bool PatientDAO::add(Patient patient)
{
    DBManager::openDB();

    QSqlQuery query;
    query.prepare(
        "INSERT INTO "
            "TPatient "
        "VALUES("
            ":Id, :Nom, :Prenom, :Adresse, :Ville, :CP, :Commentaire, :Tel, :DateConsultation, :DureeConsultation, :Priorite "
        ")"
    );

    query.bindValue(":Id", patient.getId());
    query.bindValue(":Nom", patient.getName());
    query.bindValue(":Prenom", patient.getFirstname());
    query.bindValue(":Adresse", patient.getAddress());
    query.bindValue(":Ville", patient.getCity());
    query.bindValue(":CP", patient.getZipCode());
    query.bindValue(":Commentaire", patient.getCommentary());
    query.bindValue(":Tel", patient.getPhoneNumber());
    query.bindValue(":DateConsultation", patient.getConsultationDate());
    query.bindValue(":DureeConsultation", patient.getConsultationDuration());
    query.bindValue(":Priorite", patient.getPriority());

    int result = query.exec();

    DBManager::closeDB();

    return result;
}

bool PatientDAO::remove(int id)
{
    DBManager::openDB();

    QSqlQuery query;

    query.prepare(
        "DELETE FROM "
            "TPatient "
        "WHERE "
            "Id = :Id"
    );

    query.bindValue(":Id", id);

    bool result = query.exec();

    DBManager::closeDB();

    return result;
}

bool PatientDAO::update(Patient patient)
{
    DBManager::openDB();

    QSqlQuery query;
    query.prepare(
        "UPDATE "
            "TPatient "
        "SET "
            "Nom = :Nom, Prenom = :Prenom, Adresse = :Adresse, Ville = :Ville, CP = :CP, Commentaire = :Commentaire, "
            "Tel = :Tel, DateConsultation = :DateConsultation, DureeConsultation = :DureeConsultation, Priorite = :Priorite "
        "WHERE "
            "Id = :Id"
    );

    query.bindValue(":Id", patient.getId());
    query.bindValue(":Nom", patient.getName());
    query.bindValue(":Prenom", patient.getFirstname());
    query.bindValue(":Adresse", patient.getAddress());
    query.bindValue(":Ville", patient.getCity());
    query.bindValue(":CP", patient.getZipCode());
    query.bindValue(":Commentaire", patient.getCommentary());
    query.bindValue(":Tel", patient.getPhoneNumber());
    query.bindValue(":DateConsultation", patient.getConsultationDate());
    query.bindValue(":DureeConsultation", patient.getConsultationDuration());
    query.bindValue(":Priorite", patient.getPriority());

    // Remove the old list of consultations
    consultationDAO.removeFromPatientId(patient.getId());

    // Set the new list of consultations
    QList<Resource> resources = patient.getResources();
    for (QList<Resource>::iterator it = resources.begin(); it != resources.end(); ++it)
    {
        consultationDAO.add((*it).getId(), patient.getId());
    }

    int result = query.exec();

    DBManager::closeDB();

    return result;
}

int PatientDAO::getNextId()
{
    DBManager::openDB();

    QSqlQuery query;
    query.exec(
        "SELECT "
            "MAX(Id) "
        "FROM "
             "TPatient"
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

QList<Patient> PatientDAO::getListFromSearchInfo(PatientSearchInfo patientSearchInfo)
{
    DBManager::openDB();

    QSqlQuery query;

    query.prepare(
        "SELECT "
            "Id, Nom, Prenom, Adresse, Ville, CP, Commentaire, Tel, DateConsultation, DureeConsultation, Priorite "
        "FROM "
            "TPatient "
        "WHERE "
            "CASE WHEN ((SELECT 1 FROM TPatient WHERE Id = :Id) NOT NULL) "
                "THEN Id = :Id "
            "ELSE "
                "(Nom LIKE :Nom) "
                "AND (Prenom LIKE :Prenom) "
                "AND (DateConsultation BETWEEN :PriorDate AND :LaterDate)"
            "END"
    );

    query.bindValue(":Nom", QString("%1%").arg(patientSearchInfo.name));
    query.bindValue(":Prenom", QString("%1%").arg(patientSearchInfo.firstname));
    query.bindValue(":PriorDate", patientSearchInfo.priorDate);
    query.bindValue(":LaterDate", patientSearchInfo.laterDate);
    query.bindValue(":Id", patientSearchInfo.id);

    query.exec();

    QList<Patient> patientsList;
    Patient patient;

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString firstname = query.value(2).toString();
        QString address = query.value(3).toString();
        QString city = query.value(4).toString();
        int zipCode = query.value(5).toInt();
        QString commentary = query.value(6).toString();
        int phoneNumber = query.value(7).toInt();
        QDate consultationDate = QDate::fromString(query.value(8).toString(), "yyyy-MM-dd");
        int consultationDuration = query.value(9).toInt();
        int priority = query.value(10).toInt();

        QList<Resource> resources;
        QList<int> resourceIds = consultationDAO.getResourceIdsListFromPatientId(id);
        for (int i = 0; i < resourceIds.size(); i++)
        {
            resources.append(resourceDAO.get(resourceIds.at(i)));
        }

        patient.setId(id);
        patient.setName(name);
        patient.setFirstname(firstname);
        patient.setConsultationDate(consultationDate);
        patient.setAddress(address);
        patient.setCity(city);
        patient.setZipCode(zipCode);
        patient.setConsultationDuration(consultationDuration);
        patient.setResources(resources);
        patient.setCommentary(commentary);
        patient.setPhoneNumber(phoneNumber);
        patient.setPriority(priority);

        patientsList.append(patient);
    }

    DBManager::closeDB();

    return patientsList;
}

QList<Patient> PatientDAO::getListFromConsultationDate(QDate date)
{
    DBManager::openDB();

    QSqlQuery query;

    query.prepare(
        "SELECT "
            "Id, Nom, Prenom, Adresse, Ville, CP, Commentaire, Tel, DateConsultation, DureeConsultation, Priorite "
        "FROM "
            "TPatient "
        "WHERE "
            "DateConsultation = :DateConsultation"
    );

    query.bindValue(":DateConsultation", date);

    query.exec();

    QList<Patient> patientsList;
    Patient patient;

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString firstname = query.value(2).toString();
        QString address = query.value(3).toString();
        QString city = query.value(4).toString();
        int zipCode = query.value(5).toInt();
        QString commentary = query.value(6).toString();
        int phoneNumber = query.value(7).toInt();
        QDate consultationDate = QDate::fromString(query.value(8).toString(), "yyyy-MM-dd");
        int consultationDuration = query.value(9).toInt();
        int priority = query.value(10).toInt();

        QList<Resource> resources;
        QList<int> resourceIds = consultationDAO.getResourceIdsListFromPatientId(id);
        for (int i = 0; i < resourceIds.size(); i++)
        {
            resources.append(resourceDAO.get(resourceIds.at(i)));
        }

        patient.setId(id);
        patient.setName(name);
        patient.setFirstname(firstname);
        patient.setConsultationDate(consultationDate);
        patient.setAddress(address);
        patient.setCity(city);
        patient.setZipCode(zipCode);
        patient.setConsultationDuration(consultationDuration);
        patient.setResources(resources);
        patient.setCommentary(commentary);
        patient.setPhoneNumber(phoneNumber);
        patient.setPriority(priority);

        patientsList.append(patient);
    }

    DBManager::closeDB();

    return patientsList;
}

QList<Patient> getListByConsultationDate(QDate consultationDate);
