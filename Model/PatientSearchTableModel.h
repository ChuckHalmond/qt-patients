#ifndef PATIENTSEARCHTABLEMODEL_H
#define PATIENTSEARCHTABLEMODEL_H

#include "Patient.h"

#include <QAbstractTableModel>

class PatientSearchTableModel : public QAbstractTableModel
{
    Q_OBJECT

    private:
        QList<Patient> patients;

    public:
        PatientSearchTableModel(QObject *parent = 0);
        ~PatientSearchTableModel();

        int rowCount(const QModelIndex &parent = QModelIndex()) const;
        int columnCount(const QModelIndex &parent = QModelIndex()) const;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
        QVariant headerData(int section, Qt::Orientation orientation, int role) const;

        void setRows(QList<Patient> patients);
        void insertRow(Patient patient);
        void updateRow(Patient patient);
        void removeRow(int patientId);
};

#endif // PATIENTSEARCHTABLEMODEL_H
