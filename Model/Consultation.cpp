#include "Consultation.h"

/* Constructor & destructor */

Consultation::Consultation()
{
}

Consultation::~Consultation()
{

}

/* Getters */

Resource Consultation::getResource() const
{
    return resource;
}

Patient Consultation::getPatient() const
{
    return patient;
}

QPair<int,int> Consultation::getHours() const
{
    return hours;
}

/* Setters */

void Consultation::setResource(Resource resource)
{
    this->resource = resource;
}

void Consultation::setPatient(Patient patient)
{
    this->patient = patient;
}

void Consultation::setHours(QPair<int, int> hours)
{
    this->hours = hours;
}
