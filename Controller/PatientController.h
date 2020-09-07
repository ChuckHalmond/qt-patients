#ifndef PATIENTCONTROLLER_H
#define PATIENTCONTROLLER_H

#include "Model/PatientSearchTableModel.h"
#include "Model/PatientSearchInfo.h"
#include "Model/Patient.h"
#include "DAO/PatientDAO.h"
#include "DAO/ResourceDAO.h"
#include "UI/PatientDialog.h"
#include "Model/ResourcesListModel.h"

#include <QObject>
#include <QWidget>
#include <QTableView>
#include <QAbstractTableModel>
#include <QList>
#include <QListView>

class PatientController : public QObject
{
    Q_OBJECT

    private:

        // DAO
        PatientDAO *patientDAO;
        ResourceDAO *resourceDAO; // Required to show the list of resources

        // Ui
        PatientDialog *patientDialog;
        QListView *patientAvailableResourcesListView;
        QListView *patientAllocatedResourcesListView;
        QTableView *patientSearchTableView;

        // Model
        ResourcesListModel *patientAvailableResourcesListModel;
        ResourcesListModel *patientAllocatedResourcesListModel;
        PatientSearchTableModel *patientSearchTableModel;

    public:
        PatientController(QTableView *patientSearchTableView);
        ~PatientController();

        void init();
        void finalize();

    public slots:
        // Slots related to patientSearchTableView
        void slot_handle_launchPatientSearch(const PatientSearchInfo &patientSearchInfo);
        void slot_handle_displayTableViewContextMenu(const QPoint &pos);

        // Slots related to patientDialog
        void slot_handle_editNewPatient();
        void slot_handle_editExistingPatient(/*const int &patientId*/);
        void slot_handle_validatePatientEdition();
        void slot_handle_cancelPatientEdition();
        void slot_handle_deletePatient(/*const int &patientId*/);

    signals:
        void signal_trigger_updateStatusBarMessage(const QString &messsage);

};

#endif // PATIENTCONTROLLER_H
