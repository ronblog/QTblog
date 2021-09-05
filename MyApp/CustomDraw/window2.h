#ifndef WINDOW2_H
#define WINDOW2_H

#include <QMainWindow>
#include "sharp.h"



class Window2 : public QMainWindow
{
	Q_OBJECT
public:
	explicit Window2(QWidget *parent = nullptr);

	bool (*timeFunction)();
	void (*paintFunction)(QPainter* p);

signals:

public slots:

	void on_click();

	// QWidget interface
protected:
	virtual void paintEvent(QPaintEvent *event);

	bool _init;

	QVector<Sharp*> _sharps;
	QVector<Sharp*> _sharps_next;

	int nType;
	int ms;
	int nTotal;

	int _runIndex;



	// QObject interface
protected:
	virtual void timerEvent(QTimerEvent *event);

	void runOneByOne(int id);
	void runByType(int id);
	void runByGroup(int id);

	// QWidget interface
protected:
	virtual void showEvent(QShowEvent *event);
};

#endif // WINDOW2_H
