#ifndef ADDNEW_H
#define ADDNEW_H

#include <QDialog>


class AddNewDialog : public QDialog
{
    Q_OBJECT

public:
    AddNewDialog();
    ~AddNewDialog();

public slots:
    void chooseFile(int i);
};

#endif // ADDNEW_H
