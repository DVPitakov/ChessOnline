#include "MyNet.h"
MyNet::MyNet(QObject *parent) : QObject(parent)
{
    QString out = "https://asr.yandex.net/asr_xml?uuid=01ae13cb744628b58fb536d496daa1e6&key=bae3bf9f-e3ac-4833-9821-7a0e3d1cc39c&topic=maps";
    QUrl serviceUrl = QUrl(out);
    request = QNetworkRequest(serviceUrl);
    request.setRawHeader("Content-Type","audio/x-pcm;bit=16;rate=16000");
    request.setRawHeader("User-Agent","Cursach/0.1");
    request.setRawHeader("Host", "asr.yandex.net");
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

void   MyNet::vtos(QByteArray * parr, QLabel* _Label) {
    Label = _Label;
    networkManager->post(request,* parr);
}
