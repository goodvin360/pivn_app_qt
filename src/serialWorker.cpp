#include "serialWorker.h"
#include <QDebug>

SerialWorker::SerialWorker(QObject *parent, std::string portName)
        : QObject(parent), pName(portName)
{

}

void SerialWorker::startWork()
{
    serial.setPortName(pName.data());
    serial.setBaudRate(QSerialPort::Baud115200);        // ← подставь свой
    serial.setDataBits(QSerialPort::Data7);             // ← подставь свой
    serial.setParity(QSerialPort::NoParity);            // ← подставь свой
    serial.setStopBits(QSerialPort::OneStop);           // ← подставь свой
    serial.setFlowControl(QSerialPort::NoFlowControl);  // ← подставь свой

    connect(&serial,
            &QSerialPort::readyRead,
            this,
            &SerialWorker::onReadyRead);

    if (!serial.open(QIODevice::ReadOnly)) {
        emit error(serial.errorString());
    } else {
        qDebug() << "Serial opened in thread:" << QThread::currentThread();
    }
}

void SerialWorker::stopWork()
{
    if (serial.isOpen())
        serial.close();
}

void SerialWorker::onReadyRead()
{
    QByteArray data = serial.readAll();
    emit dataReceived(data);
}