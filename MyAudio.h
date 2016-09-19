#ifndef MYAUDIO_H
#define MYAUDIO_H

#include <QObject>
#include <QtMultimedia>
#include <iostream>
#include <QFile>

class MyAudio : public QObject
{
    Q_OBJECT
    QByteArray* output_bytes;
    QAudioInput* audio_in;
    QAudioOutput* audio_out;
    QAudioFormat format;
    QBuffer buffer;
public:
    explicit MyAudio(QObject *parent = 0);
    void listen();
    void play(int start = 0, int end = -1);
    QByteArray* data()
    {
        return output_bytes;
    }

signals:

public slots:
    void in_mess(QAudio::State newState);
    void stopRecoding()
    {
        qDebug() << "I'm here";
        audio_in->stop();
        buffer.close();
    }
    void out_mess(QAudio::State newState);
};

#endif // MYAUDIO_H
