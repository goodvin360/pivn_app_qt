#include "mainCaller.h"

mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent) {

    parent = nullptr;

    this->setAttribute(Qt::WA_DeleteOnClose);

    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, this, &mainWindow::startByTimer);
    m_timer->setInterval(1000);

}

mainWindow::~mainWindow() {

}

void mainWindow::startByTimer() {
    std::string inputValStr = sPort->onReadyRead();
    std::cout << inputValStr << std::endl;
}

void mainWindow::addStart() {
    qtPort = new QSerialPort;
    sPort = new serialPort(nullptr, "COM8", qtPort);
    m_timer->start();
}

void mainWindow::addStop() {
    m_timer->stop();
    delete sPort;
}
