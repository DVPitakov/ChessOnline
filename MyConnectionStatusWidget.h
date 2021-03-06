#ifndef MYCONNECTIONFORM_H
#define MYCONNECTIONFORM_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QColor>

class MyConnectionStatusWidget : public QWidget
{
    bool isConnected{false};
    Q_OBJECT
public:
    explicit MyConnectionStatusWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent*);
signals:
public slots:
    void connected();

    void friendSearch();

    void friendFounded();
};

#endif // MYCONNECTIONFORM_H
