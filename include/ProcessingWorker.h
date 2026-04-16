#ifndef PIVN_APP_QT_SERIAL_PROCESSINGWORKER_H
#define PIVN_APP_QT_SERIAL_PROCESSINGWORKER_H

#include "QObject"
#include <QDebug>
#include "iostream"
#include "fstream"


class ProcessingWorker : public QObject {
    Q_OBJECT
public:
    ProcessingWorker();
    ~ProcessingWorker();

    int num = 0;
    std::vector <int> number;
    std::vector <std::string> portData;
    void fileWrite();
    QByteArray portDataPart;

public slots:
    void process(QByteArray data);

signals:
    void processedData(QVector<double> values);

};

#endif //PIVN_APP_QT_SERIAL_PROCESSINGWORKER_H
