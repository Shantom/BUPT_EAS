#ifndef SUBJECT_H
#define SUBJECT_H

#include <QObject>

class Subject : public QObject
{
    Q_OBJECT
public:
    explicit Subject(QObject *parent = 0);
    Subject(const Subject& src);
    QString long_id;
    QString short_id;
    QString name;
    QString name_en;
    QString credit;
    QString property;
    QString grade;
    QString reason;

signals:

public slots:
};

#endif // SUBJECT_H
