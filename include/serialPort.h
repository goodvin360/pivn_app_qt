#ifndef PIVN_APP_QT_SERIAL_SERIALPORT_H
#define PIVN_APP_QT_SERIAL_SERIALPORT_H

#include <QSerialPort>
#include "QSerialPortInfo"
#include <QDebug>
#include "QObject"

class serialPort : public QObject {
Q_OBJECT
public:
    explicit serialPort (QObject*parent, std::string portName, QSerialPort*port);
    ~serialPort();

    int ReadSerialPort(char* buffer, unsigned int buf_size);
    QByteArray dataFromPort;

public slots:
    std::string onReadyRead();

private:
    QSerialPort*serial;
};

#endif //PIVN_APP_QT_SERIAL_SERIALPORT_H
