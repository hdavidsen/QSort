#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    isMoved(false) {

    /*GUI setup***********************************************************************************/
    ui->setupUi(this);
    // TODO: Sort this out
   // this->setCentralWidget(ui->grid);
    customPlot = ui->graphWidget;

    // Setting up start & reset buttons
    connect(ui->startButton, SIGNAL(released()), this, SLOT(startButton()));
    connect(ui->resetButton, SIGNAL(released()), this, SLOT(resetButton()));

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
    // This is now done by default in qcustomplot.cpp (line 23662-236645)
    // myBars->setPen(Qt::NoPen);
    // myBars->setBrush(QColor("#3E9DE5"));
    // myBars->setWidth(1);

    // Misc setup
    ui->delayBox->setToolTip("Delay (ms)\nMax: 5000\nMin: 10");
    // This is now done by default in qcustomplot.cpp (line 12875)
    // customPlot->setBackground(QColor("#DCE0E1"));
    customPlot->xAxis->setVisible(false);
    /***********************************************************************************************/

    // Setting up the timer (and default connection)
    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(selectionSort()));

    // Setting up data points
    // TODO: take the data from somewhere else (lav prio)
    valueData << 18 << 12 << 20 << 8 << 22 << 14 << 6 << 10 << 16 << 4 << 2;
    //valueData << 4 << 10 << 3 << 5 << 1;
    resetData = valueData;
    arraySize = valueData.size();
    for (int i=1; i<=arraySize; i++) {
        keyData << i;
    }

    updateGUI();
    // Rescale to fit plots after adding them to the axis
    customPlot->rescaleAxes();

    // Debugging
    // TODO: Remove when everything works (potentially move to GUI display)
    std::cout << "Before:\n";
    for(int k=0; k<arraySize; k++){
        std::cout << valueData[k] << " " << std::flush;
    }
}

MainWindow::~MainWindow() {
    delete ui;
    delete m_timer;
}

void MainWindow::updateGUI() {
    myBars->setData(keyData, valueData);
    customPlot->replot();
}

void MainWindow::setSorter(int idx) {
    // TODO: figure out which algorithms can have multiple versions
    // (quick sort with different partitions, merge sort in-place/out-of-place etc)
    switch (idx) {
        case 0:
            if(isMoved) {
                ui->textBrowser->resize(140, 290);
                ui->textBrowser->move(0, 35);
                isMoved = false;
            }
            m_timer->disconnect();
            connect(m_timer, SIGNAL(timeout()), this, SLOT(selectionSort()));
            title->setText("Selection sort");
            customPlot->replot();
        break;
        case 1:
            if(!isMoved) {
                ui->textBrowser->resize(140, 255);
                ui->textBrowser->move(0, 70);
                isMoved = true;
            }
            title->setText("Quick sort");
            customPlot->replot();
            m_timer->disconnect();
            connect(m_timer, SIGNAL(timeout()), this,SLOT(quickSort()));
        break;
        case 2:
            if(isMoved) {
                ui->textBrowser->resize(140, 290);
                ui->textBrowser->move(0, 35);
                isMoved = false;
            }
            m_timer->disconnect();
            connect(m_timer, SIGNAL(timeout()), this, SLOT(bubbleSort()));
            title->setText("Bubble sort");
            customPlot->replot();
        break;
        case 3:
            if(isMoved) {
                ui->textBrowser->resize(140, 290);
                ui->textBrowser->move(0, 35);
                isMoved = false;
            }
            title->setText("Insertion sort");
            customPlot->replot();
            m_timer->disconnect();
            connect(m_timer, SIGNAL(timeout()), this,SLOT(insertionSort()));
        break;
        case 4:
            if(!isMoved) {
                ui->textBrowser->resize(140, 255);
                ui->textBrowser->move(0, 70);
                isMoved = true;
            }
            title->setText("Heap sort");
            customPlot->replot();
            m_timer->disconnect();
            connect(m_timer, SIGNAL(timeout()), this,SLOT(heapSort()));
        break;
        case 5:
            if(isMoved) {
                ui->textBrowser->resize(140, 290);
                ui->textBrowser->move(0, 35);
                isMoved = false;
            }
            title->setText("Merge sort");
            customPlot->replot();
            m_timer->disconnect();
            connect(m_timer, SIGNAL(timeout()), this,SLOT(mergeSort()));
        break;
        case 6:
            if(isMoved) {
                ui->textBrowser->resize(140, 290);
                ui->textBrowser->move(0, 35);
                isMoved = false;
            }
            title->setText("Bucket sort");
            customPlot->replot();
            m_timer->disconnect();
            connect(m_timer, SIGNAL(timeout()), this,SLOT(bucketSort()));
        break;
        case 7:
            if(isMoved) {
                ui->textBrowser->resize(140, 290);
                ui->textBrowser->move(0, 35);
                isMoved = false;
            }
            title->setText("Shell sort");
            customPlot->replot();
            m_timer->disconnect();
            connect(m_timer, SIGNAL(timeout()), this,SLOT(shellSort()));
        break;
        case 8:
            if(isMoved) {
                ui->textBrowser->resize(140, 290);
                ui->textBrowser->move(0, 35);
                isMoved = false;
            }
            title->setText("Counting sort");
            customPlot->replot();
            m_timer->disconnect();
            connect(m_timer, SIGNAL(timeout()), this,SLOT(countingSort()));
        break;
        case 9:
            if(isMoved) {
                ui->textBrowser->resize(140, 290);
                ui->textBrowser->move(0, 35);
                isMoved = false;
            }
            title->setText("Radix sort");
            customPlot->replot();
            m_timer->disconnect();
            connect(m_timer, SIGNAL(timeout()), this,SLOT(radixSort()));
        break;
    }
}

void MainWindow::startButton() {
    std::cout << "\nSorting:\n";
    int delay = ui->delayBox->value();
    //m_timer->setSingleShot(true);
    m_timer->start(delay);
}
