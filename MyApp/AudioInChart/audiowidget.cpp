#include "audiowidget.h"


#include <QtMultimedia/QAudioDeviceInfo>
#include <QtMultimedia/QAudioInput>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>

#include <QMessageBox>
#include <QtCharts/QXYSeries>
#include <QVBoxLayout>

XYSeriesIODevice::XYSeriesIODevice(QXYSeries *series, QObject *parent) :
	QIODevice(parent),
	m_series(series)
{
}

qint64 XYSeriesIODevice::readData(char *data, qint64 maxSize)
{
	Q_UNUSED(data)
	Q_UNUSED(maxSize)
	return -1;
}

qint64 XYSeriesIODevice::writeData(const char *data, qint64 maxSize)
{
	static const int resolution = 4;

	if (m_buffer.isEmpty()) {
		m_buffer.reserve(sampleCount);
		for (int i = 0; i < sampleCount; ++i)
			m_buffer.append(QPointF(i, 0));
	}

	int start = 0;
	const int availableSamples = int(maxSize) / resolution;
	if (availableSamples < sampleCount) {
		start = sampleCount - availableSamples;
		for (int s = 0; s < start; ++s)
			m_buffer[s].setY(m_buffer.at(s + availableSamples).y());
	}

	for (int s = start; s < sampleCount; ++s, data += resolution)
		m_buffer[s].setY(qreal(uchar(*data) -128) / qreal(128));

	m_series->replace(m_buffer);
	return (sampleCount - start) * resolution;
}

AudioWidget::AudioWidget(QWidget *parent) : QWidget(parent)
{
	m_chart = new QChart();
	m_series = new QLineSeries();
	 QAudioDeviceInfo deviceInfo =  QAudioDeviceInfo::defaultInputDevice();
	 if (deviceInfo.isNull()) {
		 QMessageBox::warning(nullptr, "audio",
							  "There is no audio input device available.");
		 return ;
	 }

	 QChartView *chartView = new QChartView(m_chart);
	 chartView->setMinimumSize(800, 600);
	 m_chart->addSeries(m_series);
	 QValueAxis *axisX = new QValueAxis;
	 axisX->setRange(0, XYSeriesIODevice::sampleCount);
	 axisX->setLabelFormat("%g");
	 axisX->setTitleText("Samples");
	 QValueAxis *axisY = new QValueAxis;
	 axisY->setRange(-1, 1);
	 axisY->setTitleText("Audio level");
	 m_chart->setAxisX(axisX, m_series);
	 m_chart->setAxisY(axisY, m_series);
	 m_chart->legend()->hide();
	 m_chart->setTitle("Data from the microphone (" + deviceInfo.deviceName() + ')');

	 QVBoxLayout *mainLayout = new QVBoxLayout(this);
	 mainLayout->addWidget(chartView);

	 QAudioFormat formatAudio;
	 formatAudio.setSampleRate(8000);
	 formatAudio.setChannelCount(1);
	 formatAudio.setSampleSize(8);
	 formatAudio.setCodec("audio/pcm");
	 formatAudio.setByteOrder(QAudioFormat::LittleEndian);
	 formatAudio.setSampleType(QAudioFormat::UnSignedInt);

	 m_audioInput = new QAudioInput(deviceInfo, formatAudio, this);

	 m_device = new XYSeriesIODevice(m_series, this);
	 m_device->open(QIODevice::WriteOnly);

	 m_audioInput->start(m_device);
}
