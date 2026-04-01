#include "serialPort.h"

#include <iostream>


serialPort::serialPort(QObject*parent, std::string portName, QSerialPort*port){
    parent = nullptr;
    serial = port;

//    connect(serialPort, &QSerialPort::readyRead, this, &SerialPort::onReadyRead);

    serial->setPortName(portName.data());
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data7);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::ReadOnly);

}

serialPort::~serialPort() {
    serial->close();
}

std::string serialPort::onReadyRead() {

    QByteArray data = serial->readAll();
    return data.toStdString();

}

int serialPort::ReadSerialPort(char *buffer, unsigned int buf_size) {

    return 0;
}
