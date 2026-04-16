#ifndef PIVN_APP_QT_SERIAL_PLOTTER_H
#define PIVN_APP_QT_SERIAL_PLOTTER_H

#include "QChart"
#include <QtCharts>
#include "Chart.h"
#include "ChartView.h"

class Plotter : public QObject {
    Q_OBJECT

public:
     Plotter ();
    ~Plotter();

public slots:
    void onParsedData(QVector<double> values);

private slots:
//    void flushToPlot();
    void plotGraph();

private:
    QLineSeries *mySeries;
    QVector<double> buffer;
    QMutex mutex;
    QTimer*timer;

//    void plotGraph();
    Chart*chart;
    ChartView*chartView;
    QValueAxis*m_axisX;
    QValueAxis*m_axisY;
    std::vector<double> vecData;
    QLineSeries*series;
    double max_y = 10;
    double max_x;
    std::vector<double> maxValVec;
    int rescaleTrig = 1;
    int rescaleSize = 200;
};

#endif //PIVN_APP_QT_SERIAL_PLOTTER_H
