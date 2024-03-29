#ifndef SEARCHPAGE_H
#define SEARCHPAGE_H

#include <QWidget>
#include <QList>
#include <QGroupBox>
#include <QRadioButton>
#include <QScrollArea>

class SearchPage : public QWidget
{
    Q_OBJECT
public:
    explicit SearchPage(QWidget *parent = nullptr);
    // init buttons for search conditions
    void initButtons(QList<QString> typeLNameist, QString category);
    // init search result eara
    void initSearchResult();

signals:
    void cardClickedSignal(int);
public slots:
    void allTypeClicked();
    void allAgeClicked();
    void allRegionClicked();
    void commonTypeClicked();
    void commonAgeClicked();
    void commonRegionClicked();
    void confirmButtonClicked();
    void cardClicked();

private:
    QList<QRadioButton *> typeButtonList;
    QList<QRadioButton *> ageButtonList;
    QList<QRadioButton *> regionButtonList;
    QGroupBox *typeBox;
    QGroupBox *ageBox;
    QGroupBox *regionBox;
    QScrollArea *resultArea;

};

#endif // SEARCHPAGE_H
