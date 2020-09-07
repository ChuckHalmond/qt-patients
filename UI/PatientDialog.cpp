#include "PatientDialog.h"
#include "ui_PatientDialog.h"

#include "Util/Tools.h"

#include <QMessageBox>
#include <limits>
#include <iostream>

PatientDialog::PatientDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PatientDialog)
{
    ui->setupUi(this);

    int maxIntValue = std::numeric_limits<int>::max();
    findChild<QLineEdit*>("patientZipCodeLineEdit")->setValidator(new QIntValidator(0, maxIntValue, this));
    findChild<QLineEdit*>("patientPhoneNumberLineEdit")->setValidator(new QIntValidator(0, maxIntValue, this));
}

PatientDialog::~PatientDialog()
{
    delete ui;
}

void PatientDialog::setPatient(Patient patient)
{
    findChild<QLineEdit*>("patientNameLineEdit")->setText(patient.getName());
    findChild<QLineEdit*>("patientFirstnameLineEdit")->setText(patient.getFirstname());
    findChild<QLineEdit*>("patientAddressLineEdit")->setText(patient.getAddress());
    findChild<QLineEdit*>("patientCityLineEdit")->setText(patient.getCity());
    findChild<QLineEdit*>("patientZipCodeLineEdit")->setText(QString::number(patient.getZipCode()));
    findChild<QLineEdit*>("patientPhoneNumberLineEdit")->setText(QString::number(patient.getPhoneNumber()));
    findChild<QDateEdit*>("patientConsultationDateDateEdit")->setDate(patient.getConsultationDate());
    findChild<QSpinBox*>("patientConsultationDurationSpinBox")->setValue(patient.getConsultationDuration());
    findChild<QSpinBox*>("patientPrioritySpinBox")->setValue(patient.getPriority());
    findChild<QLineEdit*>("patientIdLineEdit")->setText(QString::number(patient.getId()));
    // Resources are set from the PatientController
    findChild<QLineEdit*>("patientCommentaryLineEdit")->setText(patient.getCommentary());
}

QListView * PatientDialog::getPatientAvailableResourcesListView()
{
    return findChild<QListView*>("patientAvailableResourcesListView");
}

QListView * PatientDialog::getPatientAllocatedResourcesListView()
{
    return findChild<QListView*>("patientAllocatedResourcesListView");
}

QModelIndexList PatientDialog::getPatientAvailableResourcesSelectedIndexes()
{
    return getPatientAvailableResourcesListView()->selectionModel()->selectedIndexes();
}

Patient PatientDialog::getPatient()
{
    Patient patient;

    patient.setName(toTitleCase(findChild<QLineEdit*>("patientNameLineEdit")->text()));
    patient.setFirstname(toTitleCase(findChild<QLineEdit*>("patientFirstnameLineEdit")->text()));
    patient.setAddress(toTitleCase(findChild<QLineEdit*>("patientAddressLineEdit")->text()));
    patient.setCity(toTitleCase(findChild<QLineEdit*>("patientCityLineEdit")->text()));
    patient.setZipCode(findChild<QLineEdit*>("patientZipCodeLineEdit")->text().toInt());
    patient.setPhoneNumber(findChild<QLineEdit*>("patientPhoneNumberLineEdit")->text().toInt());
    patient.setConsultationDate(findChild<QDateEdit*>("patientConsultationDateDateEdit")->date());
    patient.setConsultationDuration(findChild<QSpinBox*>("patientConsultationDurationSpinBox")->value());
    patient.setPriority(findChild<QSpinBox*>("patientPrioritySpinBox")->value());
    patient.setId(findChild<QLineEdit*>("patientIdLineEdit")->text().toInt());
    // Resources are retrieved from the PatientController
    patient.setCommentary(toTitleCase(findChild<QLineEdit*>("patientCommentaryLineEdit")->text()));

    return patient;
}

bool PatientDialog::hasAnyMandatoryFieldEmpty()
{
    return isEmpty(findChild<QLineEdit*>("patientNameLineEdit")->text())
        || isEmpty(findChild<QLineEdit*>("patientFirstnameLineEdit")->text())
        || isEmpty(findChild<QLineEdit*>("patientAddressLineEdit")->text())
        || isEmpty(findChild<QLineEdit*>("patientCityLineEdit")->text())
        || isEmpty(findChild<QLineEdit*>("patientZipCodeLineEdit")->text());
}

void PatientDialog::on_cancelPatientEditionButton_clicked()
{
    emit signal_trigger_cancelPatientEdition();
}

void PatientDialog::on_validatePatientEditionButton_clicked()
{
    if (hasAnyMandatoryFieldEmpty())
    {
        alertMandatoryFieldEmpty();
    }
    else
    {
        emit signal_trigger_validatePatientEdition();
    }
}

void PatientDialog::alertMandatoryFieldEmpty()
{
    QMessageBox msgBox;
    msgBox.setText("Action impossible, un champ obligatoire (*) n'a pas été renseigné");
    msgBox.exec();
}

