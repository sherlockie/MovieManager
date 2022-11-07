#ifndef SEARCHPAGE_H
#define SEARCHPAGE_H

#include <QWidget>
#include <QList>
#include <QGroupBox>
#include <QRadioButton>

class SearchPage : public QWidget
{
    Q_OBJECT
public:
    explicit SearchPage(QWidget *parent = nullptr);
    void initButtons(QList<QString> typeLNameist, QString category);
    // void initAgeButtons(QList<QString> ageLNameist);
    // void initRegionButtons(QList<QString> regionLNameist);

signals:
public slots:
    void allTypeClicked();
    void allAgeClicked();
    void allRegionClicked();
    void commonTypeClicked();
    void commonAgeClicked();
    void commonRegionClicked();

private:
    QList<QRadioButton *> typeButtonList;
    QList<QRadioButton *> ageButtonList;
    QList<QRadioButton *> regionButtonList;
    QGroupBox *typeBox;
    QGroupBox *ageBox;
    QGroupBox *regionBox;

};

#endif // SEARCHPAGE_H
