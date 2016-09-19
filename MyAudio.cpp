#include "MyAudio.h"
MyAudio::MyAudio(QObject *parent) : QObject(parent) {
    output_bytes = new QByteArray();
    buffer.setBuffer(output_bytes);
    format.setSampleRate(16000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);
    audio_in = new QAudioInput(format, this);
    audio_out = new QAudioOutput(format, this);
    connect(audio_in, SIGNAL(stateChanged(QAudio::State)), this, SLOT(in_mess(QAudio::State)));
    connect(audio_out, SIGNAL(stateChanged(QAudio::State)),this, SLOT(out_mess(QAudio::State)));

}
void MyAudio::listen() {
    buffer.open(QIODevice::WriteOnly | QIODevice::Truncate);
    audio_in->start(&buffer);
}

void MyAudio::play(int start, int end) {
    buffer.open(QIODevice::ReadOnly);
    audio_out->start(&buffer);
}
void MyAudio::in_mess(QAudio::State newState) {

}

void MyAudio::out_mess(QAudio::State newState) {
    switch (newState) {
            case QAudio::IdleState:
                // Finished playing (no more data)
                audio_out->stop();
                buffer.close();
                break;

            case QAudio::StoppedState:
                // Stopped for other reasons
                if (audio_out->error() != QAudio::NoError) {
                    // Error handling
                }
                break;

            default:
                // ... other cases as appropriate
                break;
        }
}
