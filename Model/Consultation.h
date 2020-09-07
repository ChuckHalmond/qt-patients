#ifndef CONSULTATION_H
#define CONSULTATION_H

#include "Patient.h"
#include "Resource.h"

#include <QPair>

class Consultation
{
    private :
        /* Attributes */
       Resource resource;
       Patient patient;
       QPair<int,int> hours;

    public:
       /* Constructor & destructor */
       Consultation();
       ~Consultation();

       /* Getters */
       Resource getResource() const;
       Patient getPatient() const;
       QPair<int,int> getHours() const;

       /* Setters */
       void setResource(Resource resource);
       void setPatient(Patient patient);
       void setHours(QPair<int,int> hours);
};

#endif // CONSULTATION_H
