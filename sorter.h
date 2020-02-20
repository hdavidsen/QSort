#ifndef SORTER_H
#define SORTER_H

#include "mainwindow.h"

class Sorter : public MainWindow {
     Q_OBJECT
public:
    Sorter(QWidget *parent = nullptr);
    ~Sorter();
    //void swap(double *a, double *b);

private:
    int counter, comparator, selector, tmp, arraySize;
    bool initialized;
    QVector<double> tmpDataA, tmpDataB; // using double as qcpbars is being moody..

private slots:
    void resetButton() override;
    void selectionSort() override;
    void quickSort() override;
    void bubbleSort() override;
    void insertionSort() override;
    void heapSort() override;
    void mergeSort() override;
    void shellSort() override;
    // TODO: debug/improve these two
    void countingSort() override;
    void radixSort() override;
    // TODO: implement these
    void gravitySort() override;
    void cocktailSort() override;
    void timSort() override;
    void pigeonholeSort() override;
    void combSort() override;
    void bogoSort() override;
};

#endif // SORTER_H
