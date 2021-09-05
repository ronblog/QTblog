#include "mydbwidget.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QSqlError>
#include <QDateTime>

MyDBWidget::MyDBWidget(QWidget *parent) : QWidget(parent)
{

//	QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
//		db.setHostName("acidalia");
//		db.setDatabaseName("customdb");
//		db.setUserName("mojito");
//		db.setPassword("J0a1m8");
//		bool ok = db.open();

	//QSqlDatabase db = QSqlDatabase::database();
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE" );
	db.setDatabaseName("/Users/rong/dfnet/LookUpTable");
	db.open();

	QSqlQuery q("", db);
	q.exec("drop table Movies");

	q.exec("create table Movies (id integer primary key, Title varchar, Director varchar, Rating number)");
	q.exec("insert into Movies values (0, 'Metropolis', 'Fritz Lang', '8.4')");

	q.exec("drop table lookup");

	QFile lutFile("/Users/rong/dfnet/DDE_B2_Jn");
	if (!lutFile.open(QIODevice::ReadOnly))
	{
		qDebug() << "wrong file";
		return;
	}


	QTextStream txtStream(&lutFile);
	auto line = txtStream.readLine();
	qDebug() << line;
	auto lt = line.split(":");
	auto header = lt[1].split("|");
	q.exec("drop table lookup");
	QString sqlStr = "create table lookup ( '%1' varchar primary key";
	sqlStr = sqlStr.arg(header[0]);
	for (int n=1; n< header.size();n++)
		sqlStr += QString(", '%0' varchar").arg(header[n]);
	sqlStr += ")";
	qDebug() << sqlStr;
	q.exec(sqlStr);

	if(QSqlDatabase::database().transaction()) //启动事务操作
	{
		qDebug() << QDateTime::currentDateTime();
		while (!txtStream.atEnd())
		{
			auto line = txtStream.readLine();
			if (line.startsWith("#"))
				continue;
			auto lt = line.split("|");
			//q.exec("insert into Movies values (0, 'Metropolis', 'Fritz Lang', '8.4')");
			QString sql = "insert into lookup values (";
			for (auto s : lt)
			{
				sql += "'" + s + "',";
			}
			sql = sql.left( sql.length()-1);
			sql += ")";
			q.exec(sql);
			//qDebug() << sql;
		}
		if(!QSqlDatabase::database().commit())
		{
			qDebug() << QSqlDatabase::database().lastError(); //提交
			if(!QSqlDatabase::database().rollback())
				qDebug() << QSqlDatabase::database().lastError(); //回滚
		}
		qDebug() << QDateTime::currentDateTime();
	}


	//select * from lookup where  "Drug Name"  like "HYPE%"
	//insert into lookup values ('EYE LUBRICANTS1','901508','01','001','EYE LUBRICANTS','UU','S01XA  ','Jun16'), ('EYE LUBRICANTS2','901508','01','001','EYE LUBRICANTS','UU','S01XA  ','Jun16')


}
