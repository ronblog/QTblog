#include "slidewidget.h"
#include <QPaintEvent>
#include <QPainter>
SlideWidget::SlideWidget(QWidget *parent) : QWidget(parent)
{
	texts << "On" << "Off" << "Semi";
	value = 1;

	clrText = Qt::white;
	clrBorder = Qt::darkBlue;
	clrFocus = Qt::darkBlue;
	clrNormal = Qt::white;
	QFont font;
	QFontMetrics fm(font);
	//int pixelsWide = fm.horizontalAdvance("What's the width of this text?");
	int pixelsHigh = fm.height();
	setMinimumWidth( texts.size()*50);
	setMaximumHeight(pixelsHigh * 2);
	//startTimer(10);
	update();
}

void SlideWidget::setTerms(QStringList lt)
{
	QFont font;
	QFontMetrics fm(font);
	//int pixelsWide = fm.horizontalAdvance("What's the width of this text?");
	int pixelsHigh = fm.height();
	setMinimumWidth( lt.size()*50);
	setMinimumHeight( pixelsHigh * 2);
	texts = lt;
	update();
}

void SlideWidget::setFocusColor(QColor clr)
{
	clrFocus = clr;
	update();
}

void SlideWidget::setNormalColor(QColor clr)
{
	clrNormal = clr;
	update();
}

void SlideWidget::setBorderColor(QColor clr)
{
	clrBorder = clr;
	update();
}

void SlideWidget::setTextColor(QColor clr)
{
	clrText = clr;
	update();
}

QString SlideWidget::focusText()
{
	return texts[value];
}

int SlideWidget::focusField()
{
	return  value;
}


void SlideWidget::keyPressEvent(QKeyEvent *event)
{
}

void SlideWidget::mousePressEvent(QMouseEvent *event)
{

	value = event->pos().x() / (rect().width()/texts.count());
	//value= value==texts.count()-1?0:value+1;

	update();
}

void SlideWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.fillRect(rect() , clrNormal);
	painter.setPen(clrBorder);
	painter.drawRoundedRect(rect(),5,5);
	auto rt = rect();
	int w = rt.width()/texts.count();

	for (int n=1; n<texts.count();n++)
	{
		painter.drawLine( w*n,0,w*n,rt.height());
	}
	for (int n=0; n<texts.count();n++)
	{
		painter.setPen(clrFocus);
		painter.drawText(QRect(w*n,0,w,rt.height()), Qt::AlignCenter,texts[n]);
	}

	painter.fillRect(QRect(w*value+1,1,w-2,rt.height()-2), clrFocus);
	painter.setPen(clrText);
	painter.drawText(QRect(w*value,0,w,rt.height()), Qt::AlignCenter,texts[value]);


}

