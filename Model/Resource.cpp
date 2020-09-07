#include "Resource.h"

/* Constructor & destructor */

Resource::Resource()
{
}

Resource::~Resource()
{
}

/* Getters */

int Resource::getId() const
{
    return id;
}

QString Resource::getName() const
{
    return name;
}

QString Resource::getFirstname() const
{
    return firstname;
}

ResourceType Resource::getType() const
{
    return type;
}

/* Setters */

void Resource::setId(int id)
{
    this->id = id;
}

void Resource::setName(QString name)
{
    this->name = name;
}

void Resource::setFirstname(QString firstname)
{
    this->firstname = firstname;
}

void Resource::setType(ResourceType type)
{
    this->type = type;
}
