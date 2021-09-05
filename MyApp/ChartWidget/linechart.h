#ifndef LINECHART_H
#define LINECHART_H

#include <QWidget>

#include <QtCharts/QChartGlobal>

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class XYSeriesIODevice;

QT_BEGIN_NAMESPACE
class QAudioInput;
class QAudioDeviceInfo;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QXYSeries;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

#include <QBarSet>

class LineChart : public QWidget
{
	Q_OBJECT
public:
	explicit LineChart(QWidget *parent = nullptr);
[[deprecated("numberLineChart() is thread-unsafe. Use h() instead")]]
	void numberLineChart();
	void dateLineChart();
	void areaChart();
	void cash();
signals:

public slots:
	void slot_btn_clicked();
	void handleClicked(int index, QBarSet *barset);
	void handleClicked2(int index, QBarSet *barset);
private:
	QChart *m_chart;
	QLineSeries *m_series ;


};

#endif // LINECHART_H
