#ifndef SLIDEWIDGET_H
#define SLIDEWIDGET_H

#include <QWidget>

class SlideWidget : public QWidget
{
	Q_OBJECT
public:
	explicit SlideWidget(QWidget *parent = nullptr);

	void setTerms(QStringList lt);
	void setFocusColor(QColor clr);
	void setNormalColor(QColor clr);
	void setBorderColor(QColor clr);
	void setTextColor(QColor clr);

	QString focusText();
	int focusField();

signals:

public slots:

	// QWidget interface
protected:
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void paintEvent(QPaintEvent *event);

	// QWidget interface
protected:
	virtual void keyPressEvent(QKeyEvent *event);
	int value;
	int total;
	QStringList texts;
	QColor clrText;
	QColor clrFocus;
	QColor clrNormal;
	QColor clrBorder;
};


#endif // SLIDEWIDGET_H
