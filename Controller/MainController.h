#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "UI/MainWindow.h"
#include "UI/LearnAboutDialog.h"
#include "Controller/ResourceController.h"
#include "Controller/PatientController.h"
#include "Controller/PlanningController.h"

#include <QObject>

class MainController : public QObject
{
    Q_OBJECT

    private:
        MainWindow *mainWindow;
        LearnAboutDialog *learnAboutDialog;

        ResourceController *resourceController;
        PatientController *patientController;
        PlanningController *planningController;

    public:
        MainController();
        ~MainController();

        void init();
        void finalize();

        void initResourceController();
        void finalizeResourceController();

        void initPatientController();
        void finalizePatientController();

        void initPlanningController();
        void finalizePlanningController();

    signals:
        void signal_forward_quit();

    public slots:
        void slot_forward_quit();
        void slot_handle_learnAbout();
        void slot_handle_updateStatusBarMessage(const QString &message);
};

#endif // MAINCONTROLLER_H
