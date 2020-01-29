#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore/QTimer>
#include  "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
     MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     //void Swap(double *a, double *b);
     void setSorter(int idx);
     void updateGUI();

private slots:
    void startButton();
    void resetButton();
    void selectionSort();
    void bubbleSort();

// TODO: figure out what doesn't need to be public
public:
    Ui::MainWindow *ui;
    QTimer *m_timer;
    QCustomPlot *customPlot;
    QCPBars *myBars;
    QCPTextElement *title;
    QVector<double> keyData, valueData, resetData;
    int counter, comparator, selector, arraySize = 0;
    double swap1, swap2 = 0;
    bool isMoved;
};

#endif // MAINWINDOW_H
