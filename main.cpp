#include <iostream>
#include  <locale.h>
#include <windows.h>
#include <QCoreApplication>
#include <QSerialPort>
#include "QSerialPortInfo"
#include <QDebug>
#include <QApplication>
#include <QMainWindow>
#include "ui_mainW.h"
#include "mainCaller.h"



int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, ".UTF8");
    mainWindow *window = new mainWindow(nullptr);

    Ui::MainWindow mainW;
    mainW.setupUi(window);

    window->resize(480, 640);
    window->show();
    window->mWin = window;
    return QApplication::exec();

/*    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts()) {
        qDebug() << info.portName();
    }

    QSerialPort*serial = new QSerialPort;
    serial->setPortName("COM8");
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data7);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    // Открытие порта
    if (!serial->open(QIODevice::ReadOnly)) {
        std::cout << "Ошибка:" << serial->errorString().toStdString();
        return -1;
    }

    std::cout << "Порт открыт. Ждём данные...";

    // Чтение при поступлении данных
    QObject::connect(serial, &QSerialPort::readyRead, [serial]() {
        QByteArray data = serial->readAll();
        std::cout << "Получено:" << data.toStdString();
    });

//    while (true)
//    {
//        if (serial->waitForReadyRead(3000))
//        {
//            QByteArray data = serial->readAll();
//            std::cout << "Получено:" << data.toStdString();
//        }
//    }))

    std::cout << "Hello, World!" << std::endl;

    return app.exec(); // обязательно!
//    return 0;*/

}



