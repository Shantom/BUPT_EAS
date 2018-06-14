#include "login.h"
#include "ui_login.h"
#include <QResource>
#include <QProcess>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    setWindowTitle("Login");
    QFile nameFile("/home/shantom/Desktop/n&p.txt");
    QString name="";
    QString pwd="";
    if(nameFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream in(&nameFile);
        in>>name>>pwd;
    }
    ui->lineEdit_id->setText(name);
    ui->lineEdit_pw->setText(pwd);
    ui->lineEdit_pw->setEchoMode(QLineEdit::Password);
    QResource::registerResource("Debug /src.rcc");
    on_pushButton_getCC_clicked();
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_login_clicked()
{
    QFile file("loginInfo");
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
        QMessageBox::critical(NULL, "提示", "无法创建文件");
        return;
    }
    QTextStream out(&file);
    out<<ui->lineEdit_id->text()<<endl;
    out<<ui->lineEdit_pw->text()<<endl;
    out<<ui->lineEdit_cc->text()<<endl;
    out.flush();
    file.close();

    QProcess::execute("python login.py");

    file.setFileName("loginResult");
    if (!file.open(QIODevice::ReadOnly|QIODevice::Text)) {
        QMessageBox::critical(NULL, "提示", "无法打开文件");
        return;
    }
    QTextStream in(&file);
    QString result;
    in>>result;
    file.close();
    if(result=="True"){
        QMessageBox::information(NULL, "提示", "登录成功");
        accept();
    }
    else
    {
       QMessageBox::warning(NULL, "提示", "登录失败");
       return;
    }
//
}

void Login::on_pushButton_getCC_clicked()
{
    QProcess::execute("python getCapcha.py");

    QResource::unregisterResource("Debug /src.rcc");
    QResource::registerResource("Debug /src.rcc");
    ui->label_cc->clear();
    ui->label_cc->setPixmap(QPixmap("validateCodeAction.jpg"));
}
