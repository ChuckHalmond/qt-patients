#include "MainController.h"
#include "Model/PatientSearchInfo.h"
#include "UI/LearnAboutDialog.h"

#include <QWidget>
#include <QPushButton>
#include <QObjectList>
#include <QMenu>

#include <iostream>

MainController::MainController() :
    mainWindow(new MainWindow()),
    learnAboutDialog(new LearnAboutDialog()),
    resourceController(new ResourceController(mainWindow->getResourcesTreeView())),
    patientController(new PatientController(mainWindow->getPatientSearchTableView())),
    planningController(new PlanningController())
{
    init();
}

MainController::~MainController()
{
    finalize();

    delete planningController;
    planningController = NULL;

    delete patientController;
    patientController = NULL;

    delete resourceController;
    resourceController = NULL;

    delete learnAboutDialog;
    learnAboutDialog = NULL;

    delete mainWindow;
    mainWindow = NULL;
}

/* ResourceController */

void MainController::initResourceController()
{
    QTreeView* resourcesTreeView = mainWindow->getResourcesTreeView();

    QObject::connect(mainWindow, SIGNAL(signal_trigger_editNewResource()), resourceController, SLOT(slot_handle_editNewResource()));
    QObject::connect(resourceController, SIGNAL(signal_trigger_updateStatusBarMessage(QString)), this, SLOT(slot_handle_updateStatusBarMessage(QString)));
    QObject::connect(resourcesTreeView, SIGNAL(customContextMenuRequested(QPoint)), resourceController, SLOT(slot_handle_displayTreeViewContextMenu(QPoint)));

    resourcesTreeView->setContextMenuPolicy(Qt::CustomContextMenu);
}

void MainController::finalizeResourceController()
{
    QObject::disconnect(mainWindow, SIGNAL(signal_trigger_editNewResource()));
    QObject::disconnect(resourceController, SIGNAL(signal_trigger_updateStatusBarMessage(QString)));
}

/* Patient controller*/

void MainController::initPatientController()
{
    // Retrieve the view for the patientController from the ui ..
    QTableView* patientSearchTableView = mainWindow->getPatientSearchTableView();

    // Do connections
    QObject::connect(mainWindow, SIGNAL(signal_trigger_editNewPatient()), patientController, SLOT(slot_handle_editNewPatient()));
    QObject::connect(mainWindow, SIGNAL(signal_trigger_launchPatientSearch(PatientSearchInfo)), patientController, SLOT(slot_handle_launchPatientSearch(PatientSearchInfo)));
    QObject::connect(patientController, SIGNAL(signal_trigger_updateStatusBarMessage(QString)), this, SLOT(slot_handle_updateStatusBarMessage(QString)));
    QObject::connect(patientSearchTableView, SIGNAL(customContextMenuRequested(QPoint)), patientController, SLOT(slot_handle_displayTableViewContextMenu(QPoint)));

    // To handle right click on the table view
    patientSearchTableView->setContextMenuPolicy(Qt::CustomContextMenu);
}

void MainController::finalizePatientController()
{
    // Retrieve the view for the patientController from the ui ..
    QTableView* patientSearchTableView = mainWindow->getPatientSearchTableView();

    // Undo connections
    QObject::disconnect(mainWindow, SIGNAL(signal_trigger_editNewPatient()));
    QObject::disconnect(patientSearchTableView, SIGNAL(customContextMenuRequested(QPoint)));
    QObject::disconnect(patientController, SIGNAL(signal_trigger_updateStatusBarMessage(QString)));
}

void MainController::initPlanningController()
{
    QObject::connect(mainWindow, SIGNAL(signal_trigger_doPlanning(PlanningInfo)), planningController, SLOT(slot_handle_doPlanning(PlanningInfo)));
    QObject::connect(planningController, SIGNAL(signal_trigger_updateStatusBarMessage(QString)), this, SLOT(slot_handle_updateStatusBarMessage(QString)));
}

void MainController::finalizePlanningController()
{
    QObject::disconnect(mainWindow, SIGNAL(signal_trigger_doPlanning(PlanningInfo)));
    QObject::disconnect(planningController, SIGNAL(signal_trigger_updateStatusBarMessage(QString)));
}

void MainController::init()
{
    // Do connections
    QObject::connect(mainWindow, SIGNAL(signal_trigger_learnAbout()), this, SLOT(slot_handle_learnAbout()));
    QObject::connect(mainWindow, SIGNAL(signal_trigger_quit()), this, SLOT(slot_forward_quit()));
    QObject::connect(mainWindow, SIGNAL(signal_trigger_learnAbout()), this, SLOT(slot_handle_learnAbout()));

    // Show ui
    mainWindow->show();

    // Init the other controllers
    initResourceController();
    initPatientController();
    initPlanningController();

    mainWindow->updateStatusBarMessage("Application ouverte avec succès.");
}

void MainController::finalize()
{
    // Close ui
    mainWindow->close();

    // Undo connections
    QObject::disconnect(mainWindow, SIGNAL(signal_trigger_learnAbout()));
    QObject::disconnect(mainWindow, SIGNAL(signal_trigger_quit()));
    QObject::disconnect(mainWindow->getPatientSearchTableView(), SIGNAL(customContextMenuRequested(QPoint)));

    finalizePlanningController();
    finalizePatientController();
    finalizeResourceController();
}

void MainController::slot_handle_updateStatusBarMessage(const QString &message)
{
    mainWindow->updateStatusBarMessage(message);
}

void MainController::slot_forward_quit()
{
    emit signal_forward_quit();
}

void MainController::slot_handle_learnAbout()
{
    learnAboutDialog->show();
}
