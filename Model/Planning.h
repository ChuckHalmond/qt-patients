#ifndef PLANNING_H
#define PLANNING_H

#include "Patient.h"
#include "Resource.h"
#include "Consultation.h"

#include <QVector>
#include <QTextStream>

#include <iostream>
#include<algorithm>
#include<QTextStream>
#include<QFile>
#include <math.h>

/**
 * @brief The Planning class
 * This class contains the method to plan rendez-vous with patients
 */
class Planning
{
    public:
        Planning();
        ~Planning();

        /**
         * @brief doPlanning
         * @param patients Vector that contains the patients that have rendez-vous in the same day
         * @param resource The list of all resources available
         * @return A vector of Consultation
         */
        QVector<Consultation> doPlanning(QVector<Patient> patients, QList<Resource> resource);

        /**
         * @brief sortByPriority Sorts a vector a patient by priority
         * @param patients
         * @return vetcor of patients
         */
        QVector<Patient> sortByPriority(QVector<Patient> patients);

        /**
         * @brief printConsultations prints a vector of consultation into a stream
         * @param consultations
         * @param stream
         */
        void printConsultations(QVector<Consultation> consultations,  QTextStream *stream);
};

#endif // PLANNING_H
