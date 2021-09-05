#include "linechart.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>

#include <QMessageBox>
#include <QtCharts/QXYSeries>
#include <QVBoxLayout>
#include <QChart>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QDebug>
#include <QAreaSeries>
#include <QGridLayout>
#include <QToolButton>
#include <QStackedBarSeries>
#include <QBarSet>

LineChart::LineChart(QWidget *parent) : QWidget(parent)
{
	QGridLayout * grid = new QGridLayout(this);

	for ( int n=0; n< 4; n++ )
	{
		auto btn = new QToolButton(this);
		grid->addWidget(btn,0,n);
	}
	grid->addItem(new QSpacerItem(2,2,QSizePolicy::Preferred,QSizePolicy::Minimum),0,4);


	m_chart = new QChart();


	QChartView *chartView = new QChartView(m_chart,this);
	chartView->setMinimumSize(800, 600);


	chartView->setGeometry(0,0,500,500);
	grid->addWidget(chartView,1,0,1,5);
	chartView->show();
	setLayout(grid);
	numberLineChart();
	cash();
}

void LineChart::numberLineChart()
{
	m_chart->removeAllSeries();
	for (auto s: m_chart->axes())
		m_chart->removeAxis(s );


	m_series = new QLineSeries();
	QValueAxis *axisX = new QValueAxis;
	axisX->setRange(0, 100);
	axisX->setLabelFormat("%g");
	axisX->setTitleText("Samples");
	QValueAxis *axisY = new QValueAxis;
	axisY->setRange(-1, 1);
	axisY->setTitleText("Audio level");

	m_chart->legend()->hide();
	m_chart->setTitle("Data from the ");

	m_series->append(1,0.3);
	m_series->append(2,0.7);
	m_series->append(20,0.9);
	m_series->append(22,0.3);
	m_series->append(30,0.1);
	m_series->append(50,0.2);
	m_series->append(60,0.7);
	m_series->append(80,0.3);
	m_series->append(90,0.8);

	auto series = new QLineSeries();
	for (int n=0; n< 10; n++)
	{
		series->append(n*10, 3.0/(n+5)-0.1);
	}

	m_chart->addAxis(axisX,Qt::AlignTop);
	m_chart->addAxis(axisY,Qt::AlignLeft);


	m_chart->addSeries( series);
	m_chart->addSeries(m_series);


	qDebug() << m_series->attachAxis(axisY);
	m_series->attachAxis(axisX);
	series->attachAxis(axisY);
	series->attachAxis(axisX);

}

void LineChart::dateLineChart()
{

	m_chart->removeAllSeries();
	for (auto s: m_chart->axes())
		m_chart->removeAxis(s );

	QLineSeries *series = new QLineSeries;

	 QDateTime xValue;
	 xValue.setDate(QDate(2012, 1 , 18));
	 xValue.setTime(QTime(9, 34));
	 qreal yValue = 12;
	 series->append(xValue.toMSecsSinceEpoch(), yValue);

	 xValue.setDate(QDate(2013, 5 , 11));
	 xValue.setTime(QTime(11, 14));
	 yValue = 22;
	 series->append(xValue.toMSecsSinceEpoch(), yValue);

	 m_chart->addSeries( series);
	 QDateTimeAxis *axisX = new QDateTimeAxis;
	  axisX->setFormat("dd-MM-yyyy h:mm");
	  QValueAxis *axisY = new QValueAxis;
	  //axisX->setRange(QDateTime min, QDateTime max)
	  axisY->setRange(-100, 100);
	  axisY->setTitleText("Audio level");

	m_chart->addAxis(axisY,Qt::AlignLeft);
	m_chart->addAxis(axisX,Qt::AlignTop);

	series->attachAxis(axisY);
	series->attachAxis(axisX);

}

void LineChart::areaChart()
{
	m_chart->removeAllSeries();
	for (auto s: m_chart->axes())
		m_chart->removeAxis(s );



	//![1]
		QLineSeries *series0 = new QLineSeries();
		QLineSeries *series1 = new QLineSeries();
	//![1]

	//![2]
		*series0 << QPointF(1, 5) << QPointF(3, 7) << QPointF(7, 1) << QPointF(9, 7) << QPointF(12, 6)
				 << QPointF(16, 7) << QPointF(18, 5);
		*series1 << QPointF(1, 3) << QPointF(3, 4) << QPointF(7, 3) << QPointF(8, 2) << QPointF(12, 3)
				 << QPointF(16, 4) << QPointF(18, 3);
	//![2]

	//![3]
		QAreaSeries *series = new QAreaSeries(series0, series1);
		series->setName("Batman");
		QPen pen(0x059605);
		pen.setWidth(3);
		series->setPen(pen);

		QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
		gradient.setColorAt(0.0, 0x3cc63c);
		gradient.setColorAt(1.0, 0x26f626);
		gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
		series->setBrush(gradient);
	//![3]

	//![4]

		m_chart->addSeries(series);
		m_chart->setAnimationOptions(QChart::AllAnimations);
		m_chart->setTitle("Simple areachart example");
		m_chart->createDefaultAxes();
		m_chart->axes(Qt::Horizontal).first()->setRange(0, 20);
		m_chart->axes(Qt::Vertical).first()->setRange(0, 10);

}

void LineChart::cash()
{
	m_chart->removeAllSeries();
	for (auto s: m_chart->axes())
		m_chart->removeAxis(s );


	QStackedBarSeries* s1 = new QStackedBarSeries(nullptr);
	QBarSet* amzon = new QBarSet("amazon");
	QBarSet* walm = new QBarSet("walmart");
	QBarSet* bust = new QBarSet("bestbuy");


	QDateTime dt1;
	dt1.setDate(QDate(2012, 1 , 18));
	dt1.setTime(QTime(9, 34));

	QDateTime dt2;
	dt2.setDate(QDate(2012, 12 , 18));
	dt2.setTime(QTime(9, 34));


	for(int n=0; n<12; n++)
	{
		amzon->append(n);
		walm->append(n+3);
		bust->append(n+7);


	}
	s1->append(amzon);
	s1->append(walm);
	s1->append(bust);

	m_chart->addSeries(s1);

	QDateTimeAxis * axis = new QDateTimeAxis(this);
	axis->setMin( dt1);
	axis->setMax(dt2);
	m_chart->addAxis(axis,Qt::AlignBottom);

	QObject::connect(s1, &QStackedBarSeries::clicked, this, &LineChart::handleClicked);
}

void LineChart::slot_btn_clicked()
{
	dateLineChart();
}

void LineChart::handleClicked(int index, QBarSet *barset)
{
	 QStackedBarSeries *series = static_cast<QStackedBarSeries *>(sender());
	 auto lt = series->barSets();

	QStackedBarSeries*s = new QStackedBarSeries();
	m_chart->setTitle("Simple areachart example" + QString::number(index));

	QBarSet* m = new QBarSet("monthly");
	for (QBarSet* ss : lt)
	{
		qreal aa = ss->at(index);
		m->append( aa);
	}
	s->append(m);

	m_chart->removeAllSeries();
	for (auto s1: m_chart->axes())
		m_chart->removeAxis(s1 );

	QObject::connect(s, &QStackedBarSeries::clicked, this, &LineChart::handleClicked2);

	m_chart->addSeries(s);

}


void LineChart::handleClicked2(int index, QBarSet *barset)
{
	cash();
}
