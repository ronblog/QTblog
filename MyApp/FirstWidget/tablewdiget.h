#ifndef TABLEWDIGET_H
#define TABLEWDIGET_H

#include <QWidget>

namespace Ui {
class TableWdiget;
}

class TableWdiget : public QWidget
{
	Q_OBJECT

public:
	explicit TableWdiget(QWidget *parent = nullptr);
	~TableWdiget();

private:
	Ui::TableWdiget *ui;

	// QWidget interface
protected:
	virtual void paintEvent(QPaintEvent *event);
	QList<float> lt_datas;
	QColor bg_clr;
	QColor bd_clr;
	QList<float> drawed_datas;
	int max ;

	// QObject interface
protected:
	virtual void timerEvent(QTimerEvent *event);
};

#endif // TABLEWDIGET_H
