#ifndef PIVN_APP_QT_SERIAL_SERIALWORKER_H
#define PIVN_APP_QT_SERIAL_SERIALWORKER_H

#include <QObject>
#include <QDebug>
#include <QSerialPort>
#include "QThread"

class SerialWorker : public QObject
{
Q_OBJECT

public:
    explicit SerialWorker(QObject *parent = nullptr, std::string portName = "COM3");

public slots:
    void startWork();   // запуск
    void stopWork();    // остановка

private slots:
    void onReadyRead();

signals:
    void dataReceived(QByteArray data);
    void error(QString err);

private:
    QSerialPort serial;
    std::string pName;
    QByteArray buffer;
    void processBuffer();
};

#endif //PIVN_APP_QT_SERIAL_SERIALWORKER_H
