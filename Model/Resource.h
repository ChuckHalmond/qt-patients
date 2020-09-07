#ifndef RESOURCE_H
#define RESOURCE_H

#include "ResourceType.h"
#include <QString>

class Resource
{
    private:
        /* Attributes */
        int id;
        QString name;
        QString firstname;
        ResourceType type;

    public:
        /* Constructor & destructor */
        Resource();
        ~Resource();

        /* Getters */
        int getId() const;
        QString getName() const;
        QString getFirstname() const;
        ResourceType getType() const;

        /* Setters */
        void setId(int id);
        void setName(QString name);
        void setFirstname(QString firstname);
        void setType(ResourceType type);
};

#endif // RESOURCE_H
