#include "Planning.h"

Planning::Planning()
{
}

Planning::~Planning()
{
}

/**
 * @brief doPlanning
 * @param patients Vector that contains the patients that have rendez-vous in the same day
 * @param resource The list of all resources available
 * @return A vector of Consultation
 */
QVector<Consultation> Planning::doPlanning(QVector<Patient> patients, QList<Resource> resources)
{
    //---------------------------------- Initialisation --------------------------------------
    int hDeb = 8*60;

    //<idResource, endExam>
    QMap<int,int> endExamPerResource;

    QVector<Consultation> consultations;


    for (int i = 0; i < resources.size(); i++)
        endExamPerResource[resources[i].getId()] = hDeb;


    int patTime;    // Cumulated time of examens of one patient.
    int examTime;   // Lenght of an examen for one patient.

    //----------------------------------- Traitement ---------------------------------------------

    for (QVector<Patient>::iterator itPat = patients.begin(); itPat != patients.end(); itPat++)
    {
        examTime = int(ceil((double) itPat-> getConsultationDuration() / (double) itPat-> getResources().size()));

        patTime = hDeb;
        QList<Resource> tempResources = itPat->getResources();

        for (QList<Resource>::iterator  itResource = tempResources.begin(); itResource != tempResources.end(); ++itResource)
        {
            while (endExamPerResource[itResource->getId()] % 15 != 0)
            {
                endExamPerResource[itResource->getId()]++;
            } // Round to the next 15 minutes

            if (patTime > endExamPerResource[itResource->getId()])
            {
                endExamPerResource[itResource->getId()] = patTime;
                while (endExamPerResource[itResource->getId()] % 15 != 0)
                {
                    endExamPerResource[itResource->getId()]++;
                } //Round to the next 15 minutes
            }

            Consultation tempConsultation;

            tempConsultation.setResource(*itResource);
            tempConsultation.setPatient(*itPat);
            tempConsultation.setHours(QPair<int,int>(endExamPerResource[itResource->getId()],endExamPerResource[itResource->getId()] + examTime));

            endExamPerResource[itResource->getId()] += examTime;
            patTime = endExamPerResource[itResource->getId()];

            consultations.push_back(tempConsultation);
        }
    }

    return consultations;
}

/**
 * @brief sortByPriority Sorts a vector a patient by priority
 * @param patients
 * @return vetcor of patients
 */
QVector<Patient> Planning::sortByPriority(QVector<Patient> patients)
{
    int maxPriority;
    for (int i = 0; i < patients.size(); i++)
    {
        maxPriority = patients[i].getPriority() * 100 + patients[i].getResources().size() * 10 + patients[i].getConsultationDuration();
        for (int j = i; j < patients.size(); j++)
        {
            int priority = patients[j].getPriority() * 100 + patients[j].getResources().size() * 10 + patients[j].getConsultationDuration();
            if (priority > maxPriority)
            {
                std::swap(patients[i], patients[j]);
            }
        }
    }

    return patients;
}

/**
 * @brief printConsultations prints a vector of consultation into a stream
 * @param consultations
 * @param stream
 */
void Planning::printConsultations(QVector<Consultation> consultations, QTextStream *stream)
{
    if (consultations.size()==0)
    {
        *stream<< "Pas de rendez-vous" << endl;
    }
    else
    {
        for(QVector<Consultation>::iterator itConsult = consultations.begin(); itConsult != consultations.end(); itConsult++)
        {
            *stream<< "----------------" << endl;
            *stream<< "Patient : " << (itConsult->getPatient()).getName()<<" "<<(itConsult->getPatient()).getFirstname() << endl;
            *stream<< "Ressource : " << itConsult->getResource().getName()<<" "<<itConsult->getResource().getFirstname() << endl;
           // to print with the format "8h30"
            *stream<< "Horaires : " << itConsult->getHours().first / 60 << "h" << itConsult->getHours().first - (itConsult->getHours().first / 60) * 60
                 << " - " << itConsult->getHours().second / 60 << "h" << itConsult->getHours().second - (itConsult->getHours().second / 60) * 60 <<endl; ;
        }
    }
    // Lancer une exception si on dépasse la fin de la journée.
}
