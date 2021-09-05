#include "sharp.h"
#include <QTimerEvent>
#include <math.h>
#include <QDebug>


Sharp::Sharp(QObject *parent) : QObject(parent)
{
	_isTimerStoped = false;
	_isStarted = false;
	_groupId = 0;
}

bool Sharp::isTimeOut() const
{
	return _isTimerStoped;
}

int Sharp::groupId() const
{
	return _groupId;
}

void Sharp::setGroupId(int groupId)
{
	_groupId = groupId;
}


Spiral::Spiral():Sharp(nullptr)
{
	_path.moveTo(_center);
}

Spiral::Spiral(QPointF center, int rings):Sharp(nullptr)
{
	setCenter (center);
	_rings = rings;
	_path.moveTo(_center);
}

QPointF Spiral::center() const
{
	return _center;
}

void Spiral::setCenter(const QPointF &center)
{
	_center = center;
	_path.moveTo(_center);
	_counter = 0;
	_angleCount = 0;
	_rectWidth = 5.0;
}

void Spiral::timerEvent(QTimerEvent *event)
{
	if(_counter < _rings *360/5)
	{
		//QPoint c(width()/2,height()/2);
		//arcTo(const QRectF &rectangle, qreal startAngle, qreal sweepLength)
		_path.arcTo(QRectF(_center.x()-_rectWidth,_center.y()-_rectWidth, 2* _rectWidth,2 * _rectWidth), 0 + _angleCount,1 );
		_angleCount+=5;
		if(_angleCount%10==0)
			_rectWidth+=0.2;
		_counter++;

	}
	else
	{
		killTimer(event->timerId());
		_isTimerStoped = true;
	}

}


void Line::timerEvent(QTimerEvent *event)
{
	if (_counter < _length)
	{
		_path.lineTo(_pt);
		_pt = QPoint(_line.x1()+_sn* _counter, _line.y1()+ _cs*_counter);
		_counter++;
	}
	else
	{
		killTimer(event->timerId());
		qDebug() << "End Line" << _counter;
		_isTimerStoped = true;
	}
}

Line::Line(QObject *p):Sharp(p)
{
	_path.moveTo(0,0);
}

Line::Line(QLine ln, QObject *p):Sharp(p)
{
	setLine(ln);
}

QLine Line::line() const
{
	return _line;
}

void Line::setLine(const QLine &line)
{
	_line = line;
	_length = sqrt( _line.dx()*_line.dx() + _line.dy()* _line.dy());
	float x = _line.x2() - _line.x1();
	float y = _line.p2().y() - _line.p1().y();

	_sn = x / _length;
	_cs = y / _length;
	_counter = 0;
	_pt = _line.p1();
	_path.moveTo(_line.p1());
}


Polygon::Polygon(QObject *p) : Sharp(p)
{

}

Polygon::Polygon(QPolygonF py, QObject *p) : Sharp(p)
{
	setPolygon(py);
}

QPolygonF Polygon::polygon() const
{
	return _py;
}

void Polygon::setPolygon(const QPolygonF &py)
{
	_py = py;
	if(_py.size()==0)
		return;
	_nLine = 1;

	setLine(_nLine-1,_nLine);
	_path.moveTo(_line.p1());

}

void Polygon::setLine(int b, int e)
{

	_line = QLine(_py[b].toPoint(),_py[e].toPoint());
	_length = sqrt( _line.dx()*_line.dx() + _line.dy()* _line.dy());
	float x = _line.x2() - _line.x1();
	float y = _line.p2().y() - _line.p1().y();

	_sn = x / _length;
	_cs = y / _length;
	_counter = 0;
	_nLine++;
	_pt = _line.p1();
}

void Polygon::timerEvent(QTimerEvent *event)
{
	if(_py.size()==0)
		return;
	if(_nLine < _py.size())
	{
		if (_counter < _length)
		{
			_path.lineTo(_pt);
			_pt = QPoint(_line.x1()+_sn* _counter, _line.y1()+ _cs*_counter);
			_counter++;
		}
		else
		{
			setLine(_nLine-1,_nLine);
			qDebug() << "Line:" << _nLine;
		}
	}
	else if(_nLine == _py.size())
	{
		if (_counter < _length)
		{
			_path.lineTo(_pt);
			_pt = QPoint(_line.x1()+_sn* _counter, _line.y1()+ _cs*_counter);
			_counter++;
		}
		else
		{
			setLine(_nLine-1,0);
		}
	}
	else if (_counter < _length)
	{
		_path.lineTo(_pt);
		_pt = QPoint(_line.x1()+_sn* _counter, _line.y1()+ _cs*_counter);
		_counter++;
	}
	else
	{
		killTimer(event->timerId());
		_isTimerStoped = true;
	}


}


Circle::Circle():Sharp(){}

Circle::Circle(QPointF center, float radius):Sharp()
{
	_radius = radius;
	_center = center;
	_counter = 0;
	_path.moveTo(center.x()+ _radius, center.y());
}

void Circle::timerEvent(QTimerEvent *event)
{
	if(_counter < 360)
	{
		//QPoint c(width()/2,height()/2);
		//arcTo(const QRectF &rectangle, qreal startAngle, qreal sweepLength)
		_path.arcTo(QRectF(_center.x()-_radius,_center.y()-_radius, 2* _radius,2 * _radius), 0 + _angleCount,1 );
		_angleCount++;
		_counter++;

	}
	else
	{
		killTimer(event->timerId());
		_isTimerStoped = true;
	}
}

QRect Block::rect() const
{
	return _rect;
}

void Block::setRect(const QRect &rect)
{
	_rect = rect;

}

void Block::timerEvent(QTimerEvent *event)
{
	_path.addRect(_rect);
	killTimer(event->timerId());
	_isTimerStoped = true;

}




void Block::draw(QPainter &painter)
{
	painter.fillPath(_path,_clr);
}


void Spiral::reset()
{
	setCenter(_center);
}

void Line::reset()
{
	setLine(_line);
}

void Polygon::reset()
{
	setPolygon(_py);
}

void Circle::reset()
{
	_counter = 0;
	_angleCount = 1;
	_path.moveTo(_center.x()+ _radius, _center.y());
}

void Block::reset()
{
	setRect(_rect);
}
