#include "studentmainwindow.h"
#include <QApplication>

#include <QDialog>
#include <algorithm>
#include <ratio>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	/*
	QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
	database.setHostName("hostname");
	database.setDatabaseName("stuinfo.db");
	database.setUserName("zjuwyd");
	database.setPassword("123456");
	database.open();

	QSqlQuery query;

	query.exec("create table stuinfo (id int primary key, ) ");

	*/
    StudentMainWindow w;
    //w.show();

    return a.exec();
}
