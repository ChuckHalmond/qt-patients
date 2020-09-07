#include "Patient.h"

/* Constructor & destructor */

Patient::Patient()
{
}

Patient::~Patient()
{
}

/* Getters */

int Patient::getId() const {
    return id;
}

QString Patient::getName() const {
    return name;
}

QString Patient::getFirstname() const {
    return firstname;
}

QString Patient::getAddress() const {
    return address;
}

QString Patient::getCity() const {
    return city;
}

int Patient::getZipCode() const {
    return zipCode;
}

QDate Patient::getConsultationDate() const {
    return consultationDate;
}

int Patient::getConsultationDuration() const {
    return consultationDuration;
}

QList<Resource> Patient::getResources() const {
    return resources;
}

QString Patient::getCommentary() const {
    return commentary;
}

int Patient::getPhoneNumber() const {
    return phoneNumber;
}

int Patient::getPriority() const {
    return priority;
}

/* Setters */

void Patient::setId(int id) {
    this->id = id;
}

void Patient::setName(QString name) {
    this->name = name;
}

void Patient::setFirstname(QString firstname) {
    this->firstname = firstname;
}

void Patient::setAddress(QString address) {
    this->address = address;
}

void Patient::setCity(QString city) {
    this->city = city;
}

void Patient::setZipCode(int zipCode) {
    this->zipCode = zipCode;
}

void Patient::setConsultationDate(QDate consultationDate) {
    this->consultationDate = consultationDate;
}

void Patient::setConsultationDuration(int consultationDuration) {
    this->consultationDuration = consultationDuration;
}

void Patient::setResources(QList<Resource> resources) {
    this->resources = resources;
}

void Patient::setCommentary(QString commentary) {
    this->commentary = commentary;
}

void Patient::setPhoneNumber(int phoneNumber) {
    this->phoneNumber = phoneNumber;
}

void Patient::setPriority(int priority) {
    this->priority = priority;
}
