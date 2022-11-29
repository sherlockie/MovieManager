#ifndef ADDNEW_H
#define ADDNEW_H

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QList>
#include <QPushButton>
#include <QButtonGroup>

class AddNewDialog : public QDialog
{
    Q_OBJECT

public:
    AddNewDialog();
    ~AddNewDialog();

public slots:
    void chooseFile(int i);
    void confirmButtonClicked();

private:
    QComboBox *chooseFileBox;
    QLineEdit *inputNameLine;
    QButtonGroup * allTypeList;
    QButtonGroup * allAgeList;
    QButtonGroup * allRegionList;
};

#endif // ADDNEW_H
