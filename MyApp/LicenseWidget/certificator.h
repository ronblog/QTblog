#ifndef CERTIFICATOR_H
#define CERTIFICATOR_H

#include <QWidget>

namespace Ui {
class Certificator;
}

class Certificator : public QWidget
{
	Q_OBJECT

public:
	explicit Certificator(QWidget *parent = 0);
	~Certificator();

private slots:
	void on_pushButton_clicked();

	void on_pushButton_2_clicked();

private:
	Ui::Certificator *ui;
	QString _id;
};

#endif // CERTIFICATOR_H
