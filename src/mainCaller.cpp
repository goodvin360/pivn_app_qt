#include "mainCaller.h"
#include "Plotter.h"

mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent) {

    parent = nullptr;
    this->setAttribute(Qt::WA_DeleteOnClose);

/*    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, this, &mainWindow::startByTimer);
    m_timer->setInterval(1000);*/

    uiTimer = new QTimer(this);

    connect(uiTimer, &QTimer::timeout, this, &mainWindow::flushTextLog);
    uiTimer->start(1000);

    setupChart();

}

mainWindow::~mainWindow() {
    delete myPlotter;
}

void mainWindow::startByTimer() {

}

void mainWindow::addStart() {

    serialThread = new QThread(this);

    worker = new SerialWorker(nullptr, portName);

    worker->moveToThread(serialThread);

    connect(serialThread, &QThread::started, worker, &SerialWorker::startWork);
//    connect(worker, &SerialWorker::dataReceived, this, &mainWindow::handleData);

    connect(worker, &SerialWorker::error, this, [](QString err){qDebug() << "Serial error:" << err;});
    connect(this, &QObject::destroyed, worker, &SerialWorker::stopWork);
    connect(serialThread, &QThread::finished, worker, &QObject::deleteLater);

    serialThread->start();

    procThread = new QThread(this);
    procWorker = new ProcessingWorker();

    procWorker->moveToThread(procThread);
    connect(worker, &SerialWorker::dataReceived, procWorker, &ProcessingWorker::process);
    connect(procWorker, &ProcessingWorker::processedData, myPlotter, &Plotter::onParsedData);
    connect(procWorker, &ProcessingWorker::processedData, this, &mainWindow::textBrowserOut);
    procThread->start();


}

void mainWindow::addStop() {
//    m_timer->stop();
    serialThread->quit();
    serialThread->wait();

//    procWorker->fileWrite();

    procThread->quit();
    procThread->wait();

}

void mainWindow::handleData(QByteArray data) {
//    qDebug() << "GUI thread:" << QThread::currentThread();
    myData = data;
}


void mainWindow::getCOM(QString itemName) {
    std::string tempStr = itemName.toStdString();
    for (int i=0; i<tempStr.size(); i++) {
        if (tempStr[i]<'0'|| tempStr[i]>'9')
            tempStr.erase(0, tempStr.find(tempStr[i])+1);
    }

    int portNum = std::stoi(tempStr);

    std::stringstream portString;
    if (portNum>1 && portNum<=9) {
        portString << "COM" << portNum;
    }
    else if (portNum>9) {
        portString << "\\\\.\\COM" << portNum;
    }

    portName = portString.str();
}


void mainWindow::setupChart() {
    myPlotter = new Plotter();
}

void mainWindow::textBrowserOut(QVector<double> values) {

    QString line;
    for (double v: values) {
        line += QString::number(v) + " ";
    }

    QMutexLocker locker(&logMutex);
    logBuffer += line;
}

void mainWindow::flushTextLog() {
    QString local;
    {
        QMutexLocker locker(&logMutex);
        local.swap(logBuffer);
    }

    if (local.isEmpty())
        return;

    textBrowser->append(local);
}
