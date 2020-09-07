#include "ResourceType.h"

/* Constructors & destructor */

ResourceType::ResourceType()
{

}

ResourceType::~ResourceType()
{

}

/* Getters */

int ResourceType::getId() const
{
    return id;
}

QString ResourceType::getLabel() const
{
    return label;
}

/* Setters */

void ResourceType::setId(int id)
{
    this->id = id;
}

void ResourceType::setLabel(QString label)
{
    this->label = label;
}
