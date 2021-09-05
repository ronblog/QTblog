#include "certificator.h"
#include "ui_certificator.h"
#include <QApplication>
#include <QProcess>
#include <QDebug>

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


Certificator::Certificator(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Certificator)
{
	ui->setupUi(this);
	QProcess proc;

	QStringList args;
	args << "-c" << "ioreg -rd1 -c IOPlatformExpertDevice |  awk '/IOPlatformUUID/ { print $3; }'";
	proc.start( "/bin/bash", args );
	proc.waitForFinished();

	QString uID = proc.readAll();
	qDebug() << uID.split("\"",QString::SkipEmptyParts);
	_id = uID.split("\"",QString::SkipEmptyParts)[0];
	qDebug() << _id;
}

Certificator::~Certificator()
{
	delete ui;
}


// 私有转化算法（不能公开）
void privateConvert(char *pStr)
{
	int len = strlen(pStr);
	int i = 0;
	for(i = 0; i < len; i++)
	{
		pStr[i] = pStr[i] * pStr[i] % 128; // 爱咋写咋写
		if('\0' == pStr[i])
		{
			return;
			pStr[i] = 1;
		}
	}
}


bool RsaVerifyVector(QString id)
{
	//rsa dsp;
	/* Beauty.exe软件的认证部分， 如果不通过， 则不可以用Beauty.exe */


		// 获取Beauty.exe所在目录下的license.txt文件的第一行
		QString str = QApplication::applicationDirPath()+ "/license.txt";
		qDebug() << "file paht" << str;

		// 校验license.txt文件是否存在
		ifstream in(str.toStdString());
		if(!in)
		{
			cout << "无license.txt文件， 认证失败" << endl;

			return false;
		}

		// 获取并校验license.txt文件第一行
		string line;
		getline(in, line);
		if(line == string(""))
		{
			cout << "license.txt文件错误" << endl;
			return false;
		}

		// 获取license.txt文件指纹
		char szLine[1025] = {0};
		qDebug() << sizeof(szLine) - 1;
		strncpy(szLine, line.c_str(),1000);


		// 获取运行Beauty.exe的PC的指纹

		char szFingerPrint[1025];// = "DFEE6B250591BAD1AA7EFA7D0ACB235F"; // szPC_ID的md5值
		// 显示szFingerPrint，让Beauty.exe用户可见， 便于提供给权限控制者(Beauty.exe的开发者)
		int n=0;
		memset(szFingerPrint,0,1025);
		//memset(szPC_ID,0,1025);
		foreach(auto c, id.toUtf8())
		{
			szFingerPrint[n] = c;
			n++;
		}
		szFingerPrint[n] = '\0';
		cout << szFingerPrint << endl;
		// 私有变换
		privateConvert(szFingerPrint);

		// 判断license.txe文件指纹和PC指纹是否一致
		//qDebug() <<"size = = = " <<  sizeof(szFingerPrint) - 1;
		if(0 != strncmp(szLine, szFingerPrint,sizeof(szFingerPrint) - 2))
		{
			cout << "license.txt文件认证失败 = "<<"size = = = " <<  sizeof(szFingerPrint) - 1 <<  endl;
			cout << szLine <<    "$|$"<<  endl;
			cout << szFingerPrint << "$|$"<<  endl;

			return false;
		}


		// 软件的功能部分， 此处略去10000行功能性语句
		cout << "欢迎使用本软件" << endl;

		return true;


}


void Certificator::on_pushButton_clicked()
{
	RsaVerifyVector(_id);
}

void Certificator::on_pushButton_2_clicked()
{
	char szFingerPrint[1025];// = "DFEE6B250591BAD1AA7EFA7D0ACB235F"; // 用户提供的串

	int n=0;
	foreach(auto c, _id.toUtf8())
	{
		szFingerPrint[n] = c;
		n++;
	}
	cout << szFingerPrint << endl;
	   privateConvert(szFingerPrint);

	   char szLicenseFile[2049] = {0};
	QString str = QApplication::applicationDirPath()+ "/license.txt";

	   ofstream out(str.toStdString());
	   out << szFingerPrint << endl;

	   cout << "制作证书成功" << endl;


}
