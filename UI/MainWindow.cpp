#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Model/PatientSearchTableModel.h"
#include "Model/PatientSearchInfo.h"

#include <iostream>
#include <QDate>
#include <QDateEdit>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    updateStatusBarMessage("Application ouverte avec succès!");

    findChild<QDateEdit*>("patientSearchPriorDateDateEdit")->setDate(QDate(2010, 1, 1));
    findChild<QDateEdit*>("patientSearchLaterDateDateEdit")->setDate(QDate(2020, 1, 1));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QTreeView * MainWindow::getResourcesTreeView()
{
    return findChild<QTreeView*>("resourcesTreeView");
}

QTableView * MainWindow::getPatientSearchTableView()
{
    return findChild<QTableView*>("patientSearchTableView");
}

void MainWindow::updateStatusBarMessage(const QString &message)
{
    findChild<QStatusBar*>("statusBar")->showMessage(message);
}

void MainWindow::on_launchPatientSearchButton_clicked()
{
    PatientSearchInfo patientSearchInfo = {
        findChild<QLineEdit*>("patientSearchIdLineEdit")->text().toInt(),
        findChild<QLineEdit*>("patientSearchFirstnameLineEdit")->text(),
        findChild<QLineEdit*>("patientSearchNameLineEdit")->text(),
        findChild<QDateEdit*>("patientSearchPriorDateDateEdit")->date(),
        findChild<QDateEdit*>("patientSearchLaterDateDateEdit")->date()
    };

    updateStatusBarMessage("Recherche lancée..");

    emit signal_trigger_launchPatientSearch(patientSearchInfo);
}

void MainWindow::on_doPlanningButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "/planning.txt",tr ("Text (*.txt)"));

    PlanningInfo planningInfo = {
        fileName,
        findChild<QDateEdit*>("planningDateEdit")->date()
    };

    emit signal_trigger_doPlanning(planningInfo);
}

void MainWindow::on_editNewResourceAction_triggered()
{
    emit signal_trigger_editNewResource();
}

void MainWindow::on_editNewPatientAction_triggered()
{
    emit signal_trigger_editNewPatient();
}

void MainWindow::on_quitAction_triggered()
{
    emit signal_trigger_quit();
}

void MainWindow::on_learnAboutAction_triggered()
{
    emit signal_trigger_learnAbout();
}
