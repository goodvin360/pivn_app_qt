#include "serialWorker.h"
#include <QDebug>

SerialWorker::SerialWorker(QObject *parent, std::string portName)
        : QObject(parent), pName(portName)
{

}

void SerialWorker::startWork()
{
    serial.setPortName(pName.data());
    serial.setBaudRate(921600);        // ← подставь свой
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
    buffer.append(serial.readAll());
    processBuffer();

//    QByteArray data = serial.readAll();
//    emit dataReceived(data);
}

void SerialWorker::processBuffer() {
    while (true) {
        int start = buffer.indexOf('<');

        if (start==-1) {
            buffer.clear();
            return;
        }

        int end = buffer.indexOf('>', start);

        if (end == -1) {
            if (start>0)
                buffer.remove(0, start);
            return;
        }
        QByteArray packet = buffer.mid(start, end - start +1);

        buffer.remove(0, end+1);

        emit dataReceived(packet);
    }
}