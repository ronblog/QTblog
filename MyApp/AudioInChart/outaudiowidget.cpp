#include "outaudiowidget.h"


OutAudioWidget::OutAudioWidget(QWidget *parent) : QWidget(parent)
{

	 {
		 sourceFile.setFileName("/tmp/test.raw");
		 sourceFile.open(QIODevice::ReadOnly);

		 QAudioFormat format;
		 // Set up the format, eg.
		 format.setSampleRate(8000);
		 format.setChannelCount(1);
		 format.setSampleSize(8);
		 format.setCodec("audio/pcm");
		 format.setByteOrder(QAudioFormat::LittleEndian);
		 format.setSampleType(QAudioFormat::UnSignedInt);

		 QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
		 if (!info.isFormatSupported(format)) {
			 qWarning() << "Raw audio format not supported by backend, cannot play audio.";
			 return;
		 }

		 audio = new QAudioOutput(format, this);
		 connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));
		 audio->start(&sourceFile);
	 }
}
void OutAudioWidget::handleStateChanged(QAudio::State newState)
 {
	 switch (newState) {
		 case QAudio::IdleState:
			 // Finished playing (no more data)
			 audio->stop();
			 sourceFile.close();
			 delete audio;
			 break;

		 case QAudio::StoppedState:
			 // Stopped for other reasons
			 if (audio->error() != QAudio::NoError) {
				 // Error handling
			 }
			 break;

		 default:
			 // ... other cases as appropriate
			 break;
	 }
 }
