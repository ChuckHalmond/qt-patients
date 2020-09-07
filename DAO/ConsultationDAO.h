#ifndef CONSULTATIONDAO_H
#define CONSULTATIONDAO_H

#include <QList>

class ConsultationDAO
{
    public:
        ConsultationDAO();

        QList<int> getResourceIdsListFromPatientId(int id);
        bool removeFromPatientId(int id);
        bool add(int resourceId, int patientId);
        int getNextId();
};

#endif // CONSULTATIONDAO_H
