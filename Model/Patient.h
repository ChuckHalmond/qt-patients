#ifndef PATIENT_H
#define PATIENT_H

#include <QString>
#include <QList>
#include <QDate>
#include "Resource.h"

class Patient
{
    private:
        /* Attributes */
        int id;
        QString name;
        QString firstname;
        QString address;
        QString city;
        int zipCode;
        QDate consultationDate;
        int consultationDuration;
        QList<Resource> resources;
        QString commentary;
        int phoneNumber;
        int priority;

    public:
        /* Constructor & destructor */
        Patient();
        ~Patient();

        /* Getters */
        int getId() const;
        QString getName() const;
        QString getFirstname() const;
        QString getAddress() const;
        QString getCity() const;
        int getZipCode() const;
        QDate getConsultationDate() const;
        int getConsultationDuration() const;
        QList<Resource> getResources() const;
        QString getCommentary() const;
        int getPhoneNumber() const;
        int getPriority() const;

        /* Setters */
        void setId(int id);
        void setName(QString name);
        void setFirstname(QString firstname);
        void setAddress(QString address);
        void setCity(QString city);
        void setZipCode(int zipCode);
        void setConsultationDate(QDate consultationDate);
        void setConsultationDuration(int consultationDuration);
        void setResources(QList<Resource> resources);
        void setCommentary(QString commentary);
        void setPhoneNumber(int phoneNumber);
        void setPriority(int priority);
};

#endif // PATIENT_H
