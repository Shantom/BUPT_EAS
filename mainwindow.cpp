#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QTableWidgetItem>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Grades");

    QProcess::execute("python3 ../getGrade.py");
    QProcess::execute("python3 ../getGradeOnTerms.py");
    initTable();
    initTableOnTerms();
    ui->tabWidget->setCurrentIndex(0);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTable()
{
    QFile file("grade");
    if (!file.open(QIODevice::ReadOnly|QIODevice::Text)) {
        QMessageBox::critical(NULL, "提示", "无法dakai文件");
        return;
    }
    QTextStream in(&file);
    Subject* tmp;
    while(true)
    {
        tmp=new Subject();
        in>>tmp->long_id;

        if(tmp->long_id=="eof")
            break;
        in>>tmp->short_id>>tmp->name;
        in.readLine();
        tmp->name_en=in.readLine();
        in>>tmp->credit
                >>tmp->property>>tmp->grade>>tmp->reason;
        allGrade.append(tmp);
    }
    file.close();

    //每次选中整行
    ui->tableWidget_all->setSelectionBehavior(QAbstractItemView::SelectRows);
    //把选中模式设为单选，即每次只选中一行，而不能选中多行
    ui->tableWidget_all->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_all->setSortingEnabled(true);
    //    ui->tableWidget_all->sortByColumn(0, Qt::AscendingOrder);
    ui->tableWidget_all->horizontalHeader()->setStretchLastSection(true);

    for(auto subject:allGrade)
    {
        int nOldRowCount = ui->tableWidget_all->rowCount();
        ui->tableWidget_all->insertRow(nOldRowCount);

        QTableWidgetItem *long_id = new QTableWidgetItem(subject->long_id);
        ui->tableWidget_all->setItem(nOldRowCount, 0, long_id);
        long_id->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        QTableWidgetItem *short_id = new QTableWidgetItem(subject->short_id);
        ui->tableWidget_all->setItem(nOldRowCount, 1, short_id);
        short_id->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        QTableWidgetItem *name = new QTableWidgetItem(subject->name);
        ui->tableWidget_all->setItem(nOldRowCount, 2, name);
        name->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        QTableWidgetItem *name_en = new QTableWidgetItem(subject->name_en);
        ui->tableWidget_all->setItem(nOldRowCount, 3, name_en);
        name_en->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        QTableWidgetItem *credit = new QTableWidgetItem(subject->credit);
        ui->tableWidget_all->setItem(nOldRowCount, 4, credit);
        credit->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        QTableWidgetItem *property = new QTableWidgetItem(subject->property);
        ui->tableWidget_all->setItem(nOldRowCount, 5, property);
        property->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        QTableWidgetItem *grade = new QTableWidgetItem(subject->grade);
        ui->tableWidget_all->setItem(nOldRowCount, 6, grade);
        grade->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        QTableWidgetItem *reason = new QTableWidgetItem(subject->reason);
        ui->tableWidget_all->setItem(nOldRowCount, 7, reason);
        reason->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    }

    ui->tableWidget_all->setColumnWidth(1,50);
    ui->tableWidget_all->setColumnWidth(2,250);
    ui->tableWidget_all->setColumnWidth(3,290);
    ui->tableWidget_all->setColumnWidth(4,40);
    ui->tableWidget_all->setColumnWidth(5,60);
    ui->tableWidget_all->setColumnWidth(6,50);

}

void MainWindow::initTableOnTerms()
{
    QFile file("grade_term");
    if (!file.open(QIODevice::ReadOnly|QIODevice::Text)) {
        QMessageBox::critical(NULL, "提示", "无法dakai文件");
        return;
    }
    QTextStream in(&file);
    Subject* tmp;
    QList<Subject *> tmpList;
    while(true)
    {
//        QList<Subject *> tmpList;
        while(true)
        {
            in.readLine();//goto the next line
            tmp=new Subject();
            tmp->long_id=in.readLine();

            if(tmp->long_id.length()==0)
                break;

            if(tmp->long_id=="eof")
                goto exit;
            in>>tmp->short_id>>tmp->name;
            in.readLine();
            tmp->name_en=in.readLine().trimmed();
            in>>tmp->credit>>tmp->property>>tmp->grade;
            tmpList.append(tmp);
        }
        allGradeOnTerm.append(tmpList);
        tmpList.clear();
    }
exit:
    file.close();

    QList<QTableWidget *> tables;
    tables.append(ui->tableWidget_term_1);
    tables.append(ui->tableWidget_term_2);
    tables.append(ui->tableWidget_term_3);
    tables.append(ui->tableWidget_term_4);
    tables.append(ui->tableWidget_term_5);
    tables.append(ui->tableWidget_term_6);
    tables.append(ui->tableWidget_term_7);
    tables.append(ui->tableWidget_term_8);

    int i=0;
    for(auto term:allGradeOnTerm)
    {
        //每次选中整行
        tables[i]->setSelectionBehavior(QAbstractItemView::SelectRows);
        //把选中模式设为单选，即每次只选中一行，而不能选中多行
        tables[i]->setSelectionMode(QAbstractItemView::SingleSelection);
        tables[i]->setSortingEnabled(true);

        for(auto subject:term)
        {
            int nOldRowCount = tables[i]->rowCount();
            tables[i]->insertRow(nOldRowCount);

            QTableWidgetItem *long_id = new QTableWidgetItem(subject->long_id);
            tables[i]->setItem(nOldRowCount, 0, long_id);
            long_id->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            QTableWidgetItem *short_id = new QTableWidgetItem(subject->short_id);
            tables[i]->setItem(nOldRowCount, 1, short_id);
            short_id->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            QTableWidgetItem *name = new QTableWidgetItem(subject->name);
            tables[i]->setItem(nOldRowCount, 2, name);
            name->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            QTableWidgetItem *name_en = new QTableWidgetItem(subject->name_en);
            tables[i]->setItem(nOldRowCount, 3, name_en);
            name_en->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            QTableWidgetItem *credit = new QTableWidgetItem(subject->credit);
            tables[i]->setItem(nOldRowCount, 4, credit);
            credit->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            QTableWidgetItem *property = new QTableWidgetItem(subject->property);
            tables[i]->setItem(nOldRowCount, 5, property);
            property->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            QTableWidgetItem *grade = new QTableWidgetItem(subject->grade);
            tables[i]->setItem(nOldRowCount, 6, grade);
            grade->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);


            tables[i]->setColumnWidth(1,50);
            tables[i]->setColumnWidth(2,250);
            tables[i]->setColumnWidth(3,290);
            tables[i]->setColumnWidth(4,40);
            tables[i]->setColumnWidth(5,60);
            tables[i]->setColumnWidth(6,50);
            tables[i]->horizontalHeader()->setStretchLastSection(true);

        }
        i++;
    }

}
