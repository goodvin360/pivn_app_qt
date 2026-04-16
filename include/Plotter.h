#ifndef PIVN_APP_QT_SERIAL_PLOTTER_H
#define PIVN_APP_QT_SERIAL_PLOTTER_H

#include "QChart"
#include <QtCharts>
#include "Chart.h"
#include "ChartView.h"

class Plotter {
public:
    Plotter();
    ~Plotter();

    void plotGraph();
    Chart*chart;
    ChartView*chartView;
    QValueAxis*m_axisX;
    QValueAxis*m_axisY;
    std::vector<double> vecData;
    QLineSeries*series;
    double max_y = 10;
    double max_x;
    std::vector<double> maxValVec;
};

#endif //PIVN_APP_QT_SERIAL_PLOTTER_H
