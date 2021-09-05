#ifndef OUTAUDIOWIDGET_H
#define OUTAUDIOWIDGET_H

#include <QWidget>
#include <QAudio>
#include <QFile>
#include <QAudioOutput>
#include <QtDebug>

class OutAudioWidget : public QWidget
{
	Q_OBJECT
public:
	explicit OutAudioWidget(QWidget *parent = nullptr);

signals:

public slots:
	void handleStateChanged(QAudio::State newState);

private:
	QFile sourceFile;   // class member.
	QAudioOutput* audio; // class member.
};

#endif // OUTAUDIOWIDGET_H
