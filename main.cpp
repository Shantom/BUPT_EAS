#include "mainwindow.h"
#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Login l;
    l.show();
    MainWindow *w;
    if(l.exec()==QDialog::Accepted)
    {
        w=new MainWindow();
        w->show();
    }


    return a.exec();
}
