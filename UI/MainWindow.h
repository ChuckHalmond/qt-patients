#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Model/PatientSearchInfo.h"
#include "Model/PlanningInfo.h"

#include <QMainWindow>
#include <QTreeView>
#include <QTableView>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        Ui::MainWindow *ui;

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow(); 

        QTreeView * getResourcesTreeView();
        QTableView * getPatientSearchTableView();

        int getSelectedPatientId();
        int getSelectedResourceId();

        void updateStatusBarMessage(const QString &message);

    private slots:
        void on_launchPatientSearchButton_clicked();
        void on_doPlanningButton_clicked();

        void on_editNewResourceAction_triggered();
        void on_editNewPatientAction_triggered();

        void on_quitAction_triggered();

        void on_learnAboutAction_triggered();

signals:
        void signal_trigger_launchPatientSearch(const PatientSearchInfo &patientSearchInfo);
        void signal_trigger_doPlanning(const PlanningInfo &planningInfo);

        void signal_trigger_editNewResource();
        void signal_trigger_editNewPatient();

        void signal_trigger_quit();
        void signal_trigger_learnAbout();
};

#endif // MAINWINDOW_H
