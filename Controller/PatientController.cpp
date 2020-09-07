#include "PatientController.h"
#include "Util/DBManager.h"
#include "Model/Patient.h"
#include "Model/ResourcesListModel.h"

#include <QSqlQuery>
#include <QList>
#include <QString>
#include <QTableView>
#include <QSqlQueryModel>
#include <QMenu>

#include <iostream>

PatientController::PatientController(QTableView *patientSearchTableView) :
    patientDAO(new PatientDAO),
    resourceDAO(new ResourceDAO),
    patientDialog(new PatientDialog),
    patientAvailableResourcesListView(patientDialog->getPatientAvailableResourcesListView()),
    patientAllocatedResourcesListView(patientDialog->getPatientAllocatedResourcesListView()),
    patientSearchTableView(patientSearchTableView),
    patientAvailableResourcesListModel(new ResourcesListModel),
    patientAllocatedResourcesListModel(new ResourcesListModel),
    patientSearchTableModel(new PatientSearchTableModel)
{
    init();
}

PatientController::~PatientController()
{
    finalize();
}

void PatientController::init()
{
    patientAvailableResourcesListView->setModel(patientAvailableResourcesListModel);
    patientAllocatedResourcesListView->setModel(patientAllocatedResourcesListModel);

    patientSearchTableView->setModel(patientSearchTableModel);
    patientSearchTableModel->setRows(patientDAO->getList());

    QObject::connect(patientDialog, SIGNAL(signal_trigger_validatePatientEdition()), this, SLOT(slot_handle_validatePatientEdition()));
    QObject::connect(patientDialog, SIGNAL(signal_trigger_cancelPatientEdition()), this, SLOT(slot_handle_cancelPatientEdition()));
}

void PatientController::finalize()
{
    QObject::disconnect(patientDialog, SIGNAL(signal_trigger_validatePatientEdition()));
    QObject::disconnect(patientDialog, SIGNAL(signal_trigger_cancelPatientEdition()));

    patientSearchTableView = NULL;
    patientAvailableResourcesListView = NULL;
    patientAllocatedResourcesListView = NULL;

    delete patientSearchTableModel;
    patientSearchTableModel = NULL;

    delete patientAvailableResourcesListModel;
    patientAvailableResourcesListModel = NULL;

    delete patientAllocatedResourcesListModel;
    patientAllocatedResourcesListModel = NULL;

    delete patientDialog;
    patientDialog = NULL;

    delete resourceDAO;
    resourceDAO = NULL;

    delete patientDAO;
    patientDAO = NULL;
}

void PatientController::slot_handle_launchPatientSearch(const PatientSearchInfo &patientSearchInfo)
{
    patientSearchTableModel->setRows(patientDAO->getListFromSearchInfo(patientSearchInfo));
}

void PatientController::slot_handle_deletePatient(/*const int &patientId*/)
{
    // Retrieves the patient id
    QAction *action = qobject_cast<QAction *>(sender());
    int patientId = action->data().toInt();

    if (patientDAO->remove(patientId)) {
        patientSearchTableModel->removeRow(patientId);
    }

    emit signal_trigger_updateStatusBarMessage("La fiche patient a bien été supprimée.");
}

void PatientController::slot_handle_editExistingPatient()
{
    // Retrieves the patient id if it exists
    QAction *action = qobject_cast<QAction *>(sender());
    int patientId = action->data().toInt();
    Patient patient = patientDAO->get(patientId);

    patientAvailableResourcesListModel->setRows(resourceDAO->getList());
    patientAllocatedResourcesListModel->setRows(patient.getResources());
    patientDialog->setPatient(patient);
    patientDialog->show();

    emit signal_trigger_updateStatusBarMessage("Édition d'une fiche patient existante..");
}

void PatientController::slot_handle_editNewPatient()
{
    Patient patient;
    int patientId = patientDAO->getNextId();
    patient.setId(patientId);

    patientAvailableResourcesListModel->setRows(resourceDAO->getList());
    patientAllocatedResourcesListModel->removeRows();
    patientDialog->setPatient(patient);
    patientDialog->show();

    emit signal_trigger_updateStatusBarMessage("Édition d'une nouvelle fiche patient..");
}

void PatientController::slot_handle_displayTableViewContextMenu(const QPoint &pos)
{
    (void)pos; // In order to silent the compiler -Wunused-parameter warning

    if (!patientSearchTableView->selectionModel()->selectedRows().empty())
    {
        QMenu contextMenu;

        QAction editPatient("Éditer", this);
        QAction deletePatient("Supprimer", this);

        int patientId = patientSearchTableView->model()->index(patientSearchTableView->selectionModel()->selectedRows().at(0).row(), 0).data().toInt();

        // Embed the id of the first patient in selection
        editPatient.setData(
            patientId
        );
        deletePatient.setData(
            patientId
        );

        QObject::connect(&editPatient, SIGNAL(triggered()), this, SLOT(slot_handle_editExistingPatient()));
        QObject::connect(&deletePatient, SIGNAL(triggered()), this, SLOT(slot_handle_deletePatient()));

        contextMenu.addAction(&editPatient);
        contextMenu.addAction(&deletePatient);

        contextMenu.exec(QCursor::pos());
    }
}

void PatientController::slot_handle_validatePatientEdition()
{
    Patient patient = patientDialog->getPatient();
    patient.setResources(patientAvailableResourcesListModel->getResourcesFromIndexes(
        patientDialog->getPatientAvailableResourcesSelectedIndexes())
    );

    if (patientDAO->contains(patient.getId()))
    {
        patientDAO->update(patient);
        patientSearchTableModel->updateRow(patient);
        patientDialog->hide();
    }
    else
    {
        patientDAO->add(patient);
        patientSearchTableModel->insertRow(patient);
        patientDialog->hide();
    }

    emit signal_trigger_updateStatusBarMessage("La fiche patient a bien été enregistrée.");
}

void PatientController::slot_handle_cancelPatientEdition()
{
    patientDialog->hide();
    emit signal_trigger_updateStatusBarMessage("");
}
