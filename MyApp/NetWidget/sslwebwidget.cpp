#include "sslwebwidget.h"
#include "ui_sslwebwidget.h"
#include <QAuthenticator>
#include <QUrlQuery>

SSLWebWidget::SSLWebWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SSLWebWidget)
{
	ui->setupUi(this);

	QSslSocket::addDefaultCaCertificates( "/devel/CA.pem");
	nm = new QNetworkAccessManager();

	connect(nm, SIGNAL(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility )),
		  this, SLOT(  slotNetworkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility ) ));

	connect(nm,  &QNetworkAccessManager::proxyAuthenticationRequired,
		  this,  &SSLWebWidget::slotPproxyAuthenticationRequired);

	connect(nm, SIGNAL(sslErrors(QNetworkReply *, const QList<QSslError> &)),
		  this, SLOT(slotSslError(QNetworkReply *, const QList<QSslError> &)));

	connect(nm, SIGNAL(finished(QNetworkReply *)),
		  this, SLOT(slotFinished(QNetworkReply *)));
}

SSLWebWidget::~SSLWebWidget()
{
	delete ui;
}

void SSLWebWidget::slotFinished(QNetworkReply *reply)
{
	auto data =  reply->readAll();
	qDebug() << "data ..... "<< data;
	QImage img;
	img.loadFromData(data);
	if(img.isNull() == false)
		img.save("/rong/study.png");

	//if(data.startsWith("png"));
	ui->textEdit->setHtml(data);
}

void SSLWebWidget::slotSslError(QNetworkReply *reply, const QList<QSslError> &es)
{

	qDebug() << "SSL Error";

	if (reply->error() != QNetworkReply::NoError)
	{
		switch(reply->error()) {
		case QNetworkReply::HostNotFoundError:
			qDebug() << "HostNotFoundError";
			break;
		case QNetworkReply::ConnectionRefusedError:
			qDebug() << "ConnectionRefusedError";
			break;
		case QNetworkReply::RemoteHostClosedError:
			qDebug() << "RemoteHostClosedError";
			break;
		default:
			qDebug() << "Error" << es << reply->error();
			break;
		}
	}
	else
	{
		qDebug() << "SSL Error" << es;
	}
reply->ignoreSslErrors(es);
	auto peerCert = reply->sslConfiguration().peerCertificate();

	qDebug() << "Error All --- ";
	ui->textEdit->setHtml( reply->readAll());
}


void SSLWebWidget::slotPproxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
	qDebug() << "slot proxyAuthenticationRequired";
}

void SSLWebWidget::slotNetworkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility b)
{
	qDebug() << b;
}


void SSLWebWidget::on_pushButton_clicked()
{
	QString req = "https://t50suse2.datafax.com/DFedc?cmd=getbroadcast&type=login_html";
	QNetworkReply *reply = nm->get(QNetworkRequest(QUrl( req)));
}

void SSLWebWidget::on_pushButton_2_clicked()
{
	QString req  = "https://t50suse2.datafax.com/DFedc?cmd=authorize&username=datafax&password=ski2live&prog=&protocol=5.0.0&heartbeat=3";
	QNetworkReply *reply = nm->get(QNetworkRequest(QUrl( req)));
}

void SSLWebWidget::on_pushButton_3_clicked()
{
	QString req  = "https://t50suse2.datafax.com/DFedc?cmd=getstudylist&checktoolperms";
	QNetworkReply *reply = nm->get(QNetworkRequest(QUrl( req)));
}

void SSLWebWidget::on_pushButton_4_clicked()
{
	QString req  = "https://www.google.ca";
	QNetworkReply *reply = nm->get(QNetworkRequest(QUrl( req)));
}

void SSLWebWidget::on_pushButton_5_clicked()
{
	nm->connectToHostEncrypted("https://t50suse2.datafax.com", 443);
}

void SSLWebWidget::on_pushButton_6_clicked()
{
	QString req  = "https://t50suse2.datafax.com/DFedc?cmd=setstudy&study=154";
	QNetworkReply *reply = nm->get(QNetworkRequest(QUrl( req)));
}

void SSLWebWidget::on_pushButton_7_clicked()
{
	QString req  =  "https://t50suse2.datafax.com/DFedc?cmd=studyinfo&info=centers";
	QNetworkReply *reply = nm->get(QNetworkRequest(QUrl( req)));

}

void SSLWebWidget::on_pushButton_8_clicked()
{
	QString req  =  "https://t50suse2.datafax.com/DFedc?cmd=getimage&imageid=%24plt003";
	QNetworkReply *reply = nm->get(QNetworkRequest(QUrl( req)));
}

void SSLWebWidget::on_pushButton_9_clicked()
{
	QString req  =  "http://192.168.1.101:8000/api/users";
	//QNetworkReply *reply = nm->get(QNetworkRequest(QUrl( req)));

	QNetworkRequest request;
		//QByteArray line;
		//QEventLoop eventLoop;
		request.setUrl(QUrl("http://192.168.1.101:8000/loginnew"));
		request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
		request.setRawHeader("username", "rong");
		request.setRawHeader("csrftoken", "Good2017!");

		nm->get( request );
		//QByteArray append("{\"user\":\"david\",\"token\":\"e10adc3949ba59abbe56e057f20f883e\"}");
		//QNetworkReply* reply1 = nm->post(request, append);
		//QObject::connect(nm, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
		//eventLoop.exec();
		//line=reply->readAll();
		//qDebug() << "response:" << line;

		QUrl rsa = QUrl(req); //steam login urls
		QUrlQuery urlquery;
		urlquery.addQueryItem("username", "rong"); //first step
		urlquery.addQueryItem("password", "Good2017!"); //set communication language
		rsa.setQuery(urlquery);
		QNetworkRequest first(rsa);
		QNetworkReply *reply = nm->get(first);

}

void SSLWebWidget::on_pushButton_10_clicked()
{
	QNetworkRequest request;
		//QByteArray line;
		//QEventLoop eventLoop;
		request.setUrl(QUrl("http://192.168.1.101:8000/loginnew"));
		request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
		request.setRawHeader("username", "rong");
		request.setRawHeader("csrftoken", "Good2017!");

	QByteArray append("{\"username\":\"rong\",\"password\":\"Good2017!\"}");
	QNetworkReply* reply1 = nm->post(request, append);
}
