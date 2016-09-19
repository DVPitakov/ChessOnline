#ifndef MYLABEL_H
#define MYLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = 0);
    void addLast(QString str) {
        QString texta = text();
        texta.append("\n");
        texta.append(str);
        setText(texta);

    }

signals:

public slots:

};

#endif // MYLABEL_H
