#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "subject.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initTable();
    void initTableOnTerms();

private:
    Ui::MainWindow *ui;
    QList<Subject *> allGrade;
    QList<QList<Subject *>> allGradeOnTerm;
};

#endif // MAINWINDOW_H
