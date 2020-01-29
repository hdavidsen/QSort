#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    isMoved(false) {

    /*GUI setup***********************************************************************************/
    ui->setupUi(this);
    // TODO: Sort this out
   // this->setCentralWidget(ui->grid);
    customPlot = ui->graphWidget;

    // Setting up combo boxes
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [=](int index){ setSorter(index); });
    // TODO: set up combo box #2

    // Setting up title (this will change based on which algorithm used)
    title = new QCPTextElement(customPlot);
    title->setText("Selection sort (Default)");
    customPlot->plotLayout()->insertRow(0);
    customPlot->plotLayout()->addElement(0, 0, title);

    // Setting up the bar plot
    myBars = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    myBars->setPen(Qt::NoPen);
    myBars->setBrush(QColor("#3E9DE5"));
    myBars->setWidth(1);

    // Misc setup
    ui->delayBox->setToolTip("Delay (ms)\nMax: 5000\nMin: 10");
    customPlot->setBackground(QColor("#DCE0E1"));
    customPlot->xAxis->setVisible(false);
    /***********************************************************************************************/

    // Setting up the timer (and default connection)
    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(selectionSort()));

    // Setting up start & reset buttons
    connect(ui->startButton, SIGNAL(released()), this, SLOT(startButton()));
    connect(ui->resetButton, SIGNAL(released()), this, SLOT(resetButton()));


    // Setting up data points
    // TODO: take the data from somewhere else (lav prio)
    valueData << 18 << 12 << 20 << 8 << 22 << 2 << 14 << 6 << 10 << 16 << 4;
    resetData = valueData;
    arraySize = valueData.size();
    for (int i=1; i<=arraySize; i++) {
        keyData << i;
    }
    updateGUI();


    // Debugging
    // TODO: Remove when everything works (potentially move to GUI display)
    std::cout << "Before:\n";
    for(int k=0; k<arraySize; k++){
        std::cout << valueData[k] << "    " << std::flush;
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateGUI() {
    myBars->setData(keyData, valueData);
    customPlot->rescaleAxes();
    customPlot->replot();
}

void MainWindow::setSorter(int idx) {
    if(idx == 0){
        if(isMoved) {
            ui->textBrowser->resize(141, 281);
            ui->textBrowser->move(0, 35);
            isMoved = false;
        }
        m_timer->disconnect();
        connect(m_timer, SIGNAL(timeout()), this, SLOT(selectionSort()));
        title->setText("Selection sort");
        customPlot->replot();
    }else if(idx == 1){
        if(isMoved) {
            ui->textBrowser->resize(141, 281);
            ui->textBrowser->move(0, 35);
            isMoved = false;
        }
        m_timer->disconnect();
        connect(m_timer, SIGNAL(timeout()), this, SLOT(bubbleSort()));
        title->setText("Bubble sort");
        customPlot->replot();
    }else if(idx == 2){
        if(!isMoved) {
            ui->textBrowser->resize(141, 251);
            ui->textBrowser->move(0, 70);
            isMoved = true;
        }
        title->setText("Quick sort?");
        customPlot->replot();
    }
}

void MainWindow::startButton() {
    std::cout << "\nSorting:\n";
    int delay = ui->delayBox->value();
    m_timer->start(delay);
}

void MainWindow::resetButton() {
    counter = 0;
    selector = 0;
    valueData = resetData;
    updateGUI();
}

void MainWindow::selectionSort() {

    // Inner sorting loop
    selector = counter;
    for(comparator = counter+1; comparator < arraySize; comparator++){
        if(valueData[comparator] < valueData[selector])  {
            selector = comparator;
        }
    }

    // TODO: figure out why better swap method (supposedly in 5.14) isn't working
    //valueData.swapItemsAt(counter, min);
    // TODO: use better Qvector<> swap method
    swap1 = valueData[selector];
    swap2 = valueData[counter];
    //Swap(&swap1, &swap2);
    valueData.replace(counter, swap1);
    valueData.replace(selector, swap2);

    // Update GUI
    updateGUI();

    // Checks if the sorting algorithm has passed through the entire array
    if(counter == arraySize-2) {
        // Debugging
        // TODO: Replace with/add GUI message when everything works
        std::cout << "Doneso!\nCounter = " << counter << " | min = " << selector << " | j = " << comparator << std::endl;
        std::cout << "Final Result:" << std::endl;
        for(int k=0; k<arraySize; k++){
            std::cout << valueData[k] << " -> " << std::flush;
        }
        std::cout << ":D" << std::endl;
        // not this one
        m_timer->stop();
    }else {
        counter++;
        // Debugging
        // TODO: Remove when everything works
        for(int k=0; k<arraySize; k++) {
            std::cout << valueData[k] << "  " << std::flush;
        }
        std::cout << "\n";
    }
}

void MainWindow::bubbleSort(){
    comparator = counter;

    if (valueData[selector] > valueData[selector+1]) {
        swap1 = valueData[selector+1];
        swap2 = valueData[selector];
        //Swap(&swap1, &swap2);
        valueData.replace(selector, swap1);
        valueData.replace(selector+1, swap2);
    }
    updateGUI();

    // Checks if the sorting algorithm has passed through the entire array
    if(selector < arraySize-comparator-2){
        std::cout << "selector = " << selector << " | ";
        selector++;
    }else if(selector == arraySize-comparator-2) {
        selector=0;
        counter++;
        // Debugging
        // TODO: Remove when everything works
        std::cout << "\n";
        for(int k=0; k<arraySize; k++) {
            std::cout << valueData[k] << "  " << std::flush;
        }
        std::cout << "\n";
        if(counter == arraySize-2) {
            // Debugging
            // TODO: Replace with/add GUI message when everything works
            std::cout << "Doneso!\nCounter = " << counter << " | comparator = " << comparator << " | selector = " << selector << std::endl;
            std::cout << "Final Result:" << std::endl;
            for(int k=0; k<arraySize; k++){
                std::cout << valueData[k] << " -> " << std::flush;
            }
            std::cout << ":D" << std::endl;
            // not this one
            m_timer->stop();
        }
    }
}



// TODO(ish): not necessary (for now?)
/*
void MainWindow::Swap(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}
*/
