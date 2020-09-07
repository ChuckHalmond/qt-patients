#include "PlanningController.h"

#include <QFile>
#include <iostream>

PlanningController::PlanningController() :
    patientDAO(new PatientDAO),
    resourceDAO(new ResourceDAO),
    planning(new Planning)
{

}

PlanningController::~PlanningController()
{
    delete patientDAO;
    delete resourceDAO;
    delete planning;
}


void PlanningController::slot_handle_doPlanning(const PlanningInfo &planningInfo)
{
    QVector<Patient> patients = patientDAO->getListFromConsultationDate(planningInfo.date).toVector();

    patients = planning->sortByPriority(patients);

    QFile *file = new QFile(planningInfo.path);

    if (file->open(QIODevice::WriteOnly | QIODevice::Append)) {
        QTextStream *stream = new QTextStream(file);

        *stream << "=============================" << endl;
        *stream << "Planification du jour : " << planningInfo.date.toString("dd/MM/yyyy") << endl;

        planning->printConsultations(planning->doPlanning(patients, resourceDAO->getList()), stream);

        file->close();

        emit signal_trigger_updateStatusBarMessage("Planification réussie.");
    }
    else {
        emit signal_trigger_updateStatusBarMessage("Échec de la planification.");
    }
}
