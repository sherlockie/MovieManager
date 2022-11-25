#ifndef MOVIEBANK_H
#define MOVIEBANK_H

#include "QFileInfoList"
#include <QWidget>
#include <QFrame>
#include <QToolButton>

class movieBank : public QWidget
{
    Q_OBJECT
public:
    explicit movieBank(QWidget *parent = nullptr);
    void findAllFiles(QString path, QFileInfoList &fileList);

public slots:
    void syncButtonClicked();

signals:

};

#endif // MOVIEBANK_H
