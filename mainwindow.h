#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include  "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
     MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     void setSorter(int idx);
     void updateGUI();
     void setTimer(QString buttonState);
     int getArraySize() { return arraySize; };

protected:
     QVector<double> keyData, valueData, resetData; // using double because qcpbars is moody

private slots:
    void startButton();
    virtual void resetButton() = 0;
    virtual void selectionSort() = 0;
    virtual void quickSort() = 0;
    virtual void bubbleSort() = 0;
    virtual void insertionSort() = 0;
    virtual void heapSort() = 0;
    virtual void mergeSort() = 0;
    virtual void shellSort() = 0;
    virtual void countingSort() = 0;
    virtual void radixSort() = 0;
    // TODO: implement these
    virtual void gravitySort() = 0;
    virtual void cocktailSort() = 0;
    virtual void timSort() = 0;
    virtual void pigeonholeSort() = 0;
    virtual void combSort() = 0;
    virtual void bogoSort() = 0;

private:
    Ui::MainWindow *ui;
    QCustomPlot *customPlot;
    QCPBars *myBars;
    QCPTextElement *title;
    QTimer *m_timer;
    bool isMoved;
    int arraySize;
};

#endif // MAINWINDOW_H
