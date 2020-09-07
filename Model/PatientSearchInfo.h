#ifndef PATIENTSEARCHINFO_H
#define PATIENTSEARCHINFO_H

#include "QString"
#include "QDate"

struct PatientSearchInfo {
    int id;
    QString firstname;
    QString name;
    QDate priorDate;
    QDate laterDate;
};

#endif // PATIENTSEARCHINFO_H
