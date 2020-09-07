#include "Tools.h"
#include <QStringList>

#include <iostream>

QString toTitleCase(QString string)
{
    int size = string.size();
    int i = 0;
    bool space = true;
    if (size > 0) {
        while (i < size) {
            if (space) {
                string[i] = string[i].toUpper();
            }
            else {
                string[i] = string[i].toLower();
            }

            space = (string[i] == ' ');
            i++;
        }
    }

    return string;
}

bool isEmpty(QString string)
{
    return string.replace(" ","").size() == 0;
}
