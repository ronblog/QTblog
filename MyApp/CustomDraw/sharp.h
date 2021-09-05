#ifndef SHARP_H
#define SHARP_H

#include <QObject>
#include <QPainter>
#define PI 3.14159265

class Sharp : public QObject
{
	Q_OBJECT
public:
	explicit Sharp(QObject *parent = nullptr);

	const QPainterPath& path() {
		return _path;
	}
	const QColor color(){
		return _clr;
	}
	void setColor(QColor clr)
	{
		_clr = clr;
	}

	bool isTimeOut() const;
	void start(int ms=10)
	{
		if (!_isStarted)
		{
			_isStarted = true;
			startTimer(ms);
		}
	}
	bool isStarted()
	{
		return  _isStarted;
	}

	virtual void draw(QPainter& painter)
	{
		painter.save();
		painter.setPen(QPen(color(),2,Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin));
		painter.drawPath(_path);
		painter.restore();
	}

	int groupId() const;
	void setGroupId(int groupId);

	void reStart()
	{
		_path.clear();
		_isStarted = false;
		_isTimerStoped = false;
		killTimer(0);
		reset();
	}


protected:

	virtual void reset() = 0;

	QPainterPath _path;
	QColor _clr;
	bool _isTimerStoped;
	bool _isStarted;
	int _groupId;
signals:
	void pathFinished();

public slots:
};

class Spiral : public Sharp
{
public:
	Spiral();
	Spiral(QPointF center, int rings);


	int _rings;

	// QObject interface
	QPointF center() const;
	void setCenter(const QPointF &center);

protected:
	virtual void timerEvent(QTimerEvent *event);
	QPointF _center;

	int _counter = 0;
	int _angleCount = 0;
	float _rectWidth = 5.0;

	// Sharp interface
public:
	virtual void reset();
};

class Line :public Sharp
{
public:
	Line(QObject* p = nullptr);

	Line(QLine ln,QObject* p = nullptr);

	// QObject interface
	QLine line() const;
	void setLine(const QLine &line);

protected:
	virtual void timerEvent(QTimerEvent *event);
	QLine _line;
	float _sn;
	float _cs;
	int _counter;
	int _length;
	QPoint _pt;

	// Sharp interface
public:
	virtual void reset();
};

class Polygon : public Sharp
{
public:
	Polygon(QObject* p = nullptr);

	Polygon(QPolygonF py, QObject* p = nullptr);

	QPolygonF polygon() const;
	void setPolygon(const QPolygonF &py);

private:
	QPolygonF _py;
	QLine _line;
	float _sn;
	float _cs;
	int _counter;
	int _length;
	QPoint _pt;

	int _nLine;

	void setLine(int b, int e);


	// QObject interface
protected:
	virtual void timerEvent(QTimerEvent *event);

	// Sharp interface
public:
	virtual void reset();
};

class Circle : public Sharp
{
public:

	Circle();
	Circle(QPointF center, float radius);


	QPointF _center;
	float _radius;
	int _counter = 0;
	int _angleCount = 0;


	// QObject interface
protected:
	virtual void timerEvent(QTimerEvent *event);

	// Sharp interface
public:
	virtual void reset();
};

class Block : public Sharp
{
public:
	Block(QObject* parent = nullptr):Sharp(parent)
	{

	}

	Block(QRect rt,QObject* parent = nullptr):Sharp(parent)
	{
		setRect(rt);
	}

	QRect rect() const;
	void setRect(const QRect &rect);

private:
	QRect _rect;

	// QObject interface
protected:
	virtual void timerEvent(QTimerEvent *event);

	// Sharp interface
public:
	virtual void draw(QPainter &painter);

	// Sharp interface
public:
	virtual void reset();
};

#endif // SHARP_H
