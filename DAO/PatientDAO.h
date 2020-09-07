#ifndef PATIENTDAO_H
#define PATIENTDAO_H

#include "Model/Patient.h"
#include "Model/PatientSearchInfo.h"
#include "ResourceDAO.h"
#include "ConsultationDAO.h"

class PatientDAO
{
    private:
        ResourceDAO resourceDAO;
        ConsultationDAO consultationDAO;

    public:
        PatientDAO();
        ~PatientDAO();

        Patient get(int id);
        QList<Patient> getList();

        bool add(Patient patient);
        bool contains(int id);
        bool remove(int id);
        bool update(Patient patient);
        int getNextId();

        QList<Patient> getListFromSearchInfo(PatientSearchInfo patientSearchInfo);
        QList<Patient> getListFromConsultationDate(QDate date);
};

#endif // PATIENTDAO_H
