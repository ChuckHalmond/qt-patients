#ifndef RESOURCETYPE_H
#define RESOURCETYPE_H

#include <QString>

class ResourceType
{
    private:
        /* Attributes */
        int id;
        QString label;

    public:
        /* Constructors & destructor */
        ResourceType();
        ~ResourceType();

        /* Getters */
        int getId() const;
        QString getLabel() const;

        /* Setters */
        void setId(int id);
        void setLabel(QString label);
};

#endif // RESOURCETYPE_H
