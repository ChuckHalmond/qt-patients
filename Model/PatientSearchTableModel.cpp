#include "PatientSearchTableModel.h"

PatientSearchTableModel::PatientSearchTableModel(QObject *parent) :
    QAbstractTableModel(parent),
    patients(QList<Patient>())
{
}

PatientSearchTableModel::~PatientSearchTableModel()
{
}

int PatientSearchTableModel::rowCount(const QModelIndex &/*parent*/) const
{
   return patients.size();
}

int PatientSearchTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 4;
}

QVariant PatientSearchTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= patients.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        Patient patient = patients.at(index.row());

        if (index.column() == 0)
            return patient.getId();
        else if (index.column() == 1)
            return patient.getName();

        else if (index.column() == 2)
            return patient.getFirstname();

        else if (index.column() == 3)
            return patient.getConsultationDate();
    }

    return QVariant();
}

QVariant PatientSearchTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section) {
        case 0:
            return QString("Numéro");
        case 1:
            return QString("Nom");
        case 2:
            return QString("Prénom");
        case 3:
            return QString("Date de rendez-vous");
        }
    }
    return QVariant();
}

void PatientSearchTableModel::setRows(QList<Patient> patients)
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    endRemoveRows();

    this->patients.clear();

    beginInsertRows(QModelIndex(), 0, patients.size());

    for (QList<Patient>::iterator it = patients.begin(); it != patients.end(); ++it)
    {
        this->patients.append(*it);
    }

    endInsertRows();
}

void PatientSearchTableModel::insertRow(Patient patient)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    this->patients.append(patient);

    endInsertRows();
}

void PatientSearchTableModel::updateRow(Patient patient)
{
    for (int rowIdx = 0; rowIdx < rowCount(); rowIdx++)
    {
        if (data(index(rowIdx, 0)).toInt() == patient.getId())
        {
            beginRemoveRows(QModelIndex(), rowIdx, rowIdx);
            endRemoveRows();

            beginInsertRows(QModelIndex(), rowIdx, rowIdx);

            for (QList<Patient>::iterator it = patients.begin(); it != patients.end(); ++it)
            {
                if ((*it).getId() == patient.getId()) {
                    this->patients.replace(it - patients.begin(), patient);
                    break;
                }
            }

            endInsertRows();
            break;
        }
    }
}

void PatientSearchTableModel::removeRow(int patientId)
{
    for (int rowIdx = 0; rowIdx < rowCount(); rowIdx++)
    {
        if (data(index(rowIdx, 0)).toInt() == patientId)
        {
            beginRemoveRows(QModelIndex(), rowIdx, rowIdx);

            for (QList<Patient>::iterator it = patients.begin(); it != patients.end(); ++it)
            {
                if ((*it).getId() == patientId)
                {
                    this->patients.erase(it);
                    break;
                }
            }

            endRemoveRows();
            break;
        }
    }
}

