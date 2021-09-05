#ifndef AUDIOWIDGET_H
#define AUDIOWIDGET_H

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

class XYSeriesIODevice : public QIODevice
{
	Q_OBJECT
public:
	explicit XYSeriesIODevice(QXYSeries *series, QObject *parent = nullptr);

	static const int sampleCount = 2000;

protected:
	qint64 readData(char *data, qint64 maxSize) override;
	qint64 writeData(const char *data, qint64 maxSize) override;

private:
	QXYSeries *m_series;
	QVector<QPointF> m_buffer;
};

class AudioWidget : public QWidget
{
	Q_OBJECT
public:
	explicit AudioWidget(QWidget *parent = nullptr);

signals:

public slots:

private:
	XYSeriesIODevice *m_device = nullptr;
	QChart *m_chart;
	QLineSeries *m_series ;
	QAudioInput *m_audioInput = nullptr;
};

#endif // AUDIOWIDGET_H
