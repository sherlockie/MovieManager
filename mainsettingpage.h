#ifndef MAINSETTINGPAGE_H
#define MAINSETTINGPAGE_H

#include <QDialog>
#include <QFrame>
#include <QStackedWidget>
#include <QToolButton>
#include <QLabel>

class mainSettingPage : public QDialog
{
    Q_OBJECT
public:
    mainSettingPage();
    QWidget *initEmptySettingPage();

public slots:
    void movieBankButtonClicked();

private:
    QStackedWidget *rightWin;
};

#endif // MAINSETTINGPAGE_H
