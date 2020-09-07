#ifndef LEARNABOUTDIALOG_H
#define LEARNABOUTDIALOG_H

#include <QDialog>

namespace Ui {
    class LearnAboutDialog;
}

class LearnAboutDialog : public QDialog
{
    Q_OBJECT

    private:
        Ui::LearnAboutDialog *ui;

    public:
        explicit LearnAboutDialog(QWidget *parent = 0);
        ~LearnAboutDialog();
};

#endif // LEARNABOUTDIALOG_H
