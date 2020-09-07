#ifndef PLANNINGCONTROLLER_H
#define PLANNINGCONTROLLER_H

#include "Model/PlanningInfo.h"
#include "Model/Planning.h"
#include "DAO/PatientDAO.h"
#include "DAO/ResourceDAO.h"

class PlanningController : public QObject
{
    Q_OBJECT

    private :
        PatientDAO *patientDAO;
        ResourceDAO *resourceDAO;
        Planning *planning;

    public:
        PlanningController();
        ~PlanningController();

    public slots:
        void slot_handle_doPlanning(const PlanningInfo &planningInfo);

    signals:
        void signal_trigger_updateStatusBarMessage(const QString &messsage);

};

#endif // PLANNINGCONTROLLER_H
