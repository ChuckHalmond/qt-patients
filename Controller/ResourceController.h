#ifndef RESOURCECONTROLLER_H
#define RESOURCECONTROLLER_H

#include "DAO/ResourceDAO.h"
#include "DAO/ResourceTypeDAO.h"
#include "DAO/UserDAO.h"
#include "UI/ResourceDialog.h"
#include "Model/ResourceTreeModel.h"

#include <QObject>
#include <QTreeView>

class ResourceController : public QObject
{
    Q_OBJECT

    private:
        /* Attributes */
        ResourceDAO *resourceDAO;
        ResourceTypeDAO *resourceTypeDAO;
        UserDAO *userDAO;
        ResourceDialog *resourceDialog;

        /* Ui */
        QTreeView *resourcesTreeView;

        /* Model */
        ResourceTreeModel *resourceTreeModel;

    public:
        /* Constructor & destructor */
        ResourceController(QTreeView *resourcesTreeView);
        ~ResourceController();

        void init();
        void finalize();

        void createTreeView();
        void destroyTreeView();

    public slots:
        void slot_handle_displayTreeViewContextMenu(const QPoint &pos);
        void slot_handle_editNewResource();
        void slot_handle_editExistingResource(/*const int &resourceId*/);
        void slot_handle_validateResourceEdition();
        void slot_handle_cancelResourceEdition();
        void slot_handle_deleteResource(/*const int &resourceId*/);

    signals:
        void signal_trigger_updateStatusBarMessage(const QString &messsage);
};

#endif // RESOURCECONTROLLER_H
