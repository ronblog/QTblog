#ifndef SSLWEBWIDGET_H
#define SSLWEBWIDGET_H

#include <QWidget>

#include <QNetworkReply>

namespace Ui {
class SSLWebWidget;
}

class SSLWebWidget : public QWidget
{
	Q_OBJECT

public:
	explicit SSLWebWidget(QWidget *parent = 0);
	~SSLWebWidget();
private slots:
	void on_pushButton_clicked();

	void slotFinished(QNetworkReply *reply);
	void slotSslError(QNetworkReply *reply, const QList<QSslError> &es);
	void  slotNetworkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility );
	void slotPproxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator);
	void on_pushButton_2_clicked();

	void on_pushButton_3_clicked();

	void on_pushButton_4_clicked();

	void on_pushButton_5_clicked();

	void on_pushButton_6_clicked();

	void on_pushButton_7_clicked();

	void on_pushButton_8_clicked();

	void on_pushButton_9_clicked();

	void on_pushButton_10_clicked();

private:
	Ui::SSLWebWidget *ui;
	QNetworkAccessManager* nm;
};

#endif // SSLWEBWIDGET_H
