#ifndef PATIENTDIALOG_H
#define PATIENTDIALOG_H

#include "Model/Patient.h"
#include <QDialog>
#include <QListView>

namespace Ui {
    class PatientDialog;
}

class PatientDialog : public QDialog
{
    Q_OBJECT

    private:
        Ui::PatientDialog *ui;

    public:
        explicit PatientDialog(QWidget *parent = 0);
        ~PatientDialog();

        void setPatient(Patient patient);
        Patient getPatient();

        QListView * getPatientAvailableResourcesListView();
        QListView * getPatientAllocatedResourcesListView();
        QModelIndexList getPatientAvailableResourcesSelectedIndexes();

        bool hasAnyMandatoryFieldEmpty();
        void alertMandatoryFieldEmpty();

    private slots:
        void on_cancelPatientEditionButton_clicked();
        void on_validatePatientEditionButton_clicked();

    signals:
        void signal_trigger_cancelPatientEdition();
        void signal_trigger_validatePatientEdition();

};

#endif // PATIENTDIALOG_H
