#include "sorter.h"
#include <iostream>

Sorter::Sorter(QWidget *parent) : MainWindow(parent) {
    counter = 0;
    comparator = 0;
    selector = 0;
    initialized = false;
}

Sorter::~Sorter() {

}

void Sorter::resetButton() {
    counter = 0;
    comparator = 0;
    selector = 0;
    initialized = false;
    tmpData.clear();
    valueData = resetData;
    updateGUI();
}

void Sorter::selectionSort() {
    selector = counter;

    // Inner sorting loop
    for(comparator = counter+1; comparator < arraySize; comparator++){
        if(valueData[comparator] < valueData[selector])  {
            selector = comparator;
        }
    }

    // TODO: figure out why better swap method (supposedly in 5.14) isn't working --
    // --> valueData.swapItemsAt(counter, min);
    // TODO: use better Qvector<> swap method
    tmp = valueData[counter];
    //Swap(&swap1, &swap2);
    valueData.replace(counter, valueData[selector]);
    valueData.replace(selector, tmp);

    // Update GUI
    updateGUI();

    // Checks if the sorting algorithm has passed through the entire array
    if(counter == arraySize-2) {
        // Debugging
        // TODO: Replace with/add GUI message when everything works
        std::cout << "Final Result:" << std::endl;
        for(int k=0; k<arraySize; k++){
            std::cout << valueData[k] << " -> " << std::flush;
        }
        std::cout << ":D" << std::endl;
        // keep this one
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

void Sorter::quickSort() {
    if(!initialized) {

        comparator = arraySize-1;
        // Create an auxiliary stack
        tmpData.resize(comparator - selector + 1);

        // initialize top of stack
        counter = -1;

        // push initial values of l and h to stack
        tmpData[++counter] = selector;
        tmpData[++counter] = comparator;

        initialized = true;
    }
    // l = selector, h = comparator, top = counter

    // Keep popping from stack while is not empty
    if (counter >= 0) {
        // Pop h and l
        comparator = tmpData[counter--];
        selector = tmpData[counter--];

        // Set pivot element at its correct position
        // in sorted array
        //int p = partition(selector, comparator);
        auto p = [&]() -> int{
                int i = (selector - 1);

                for (int j = selector; j <= comparator - 1; j++) {
                    if (valueData[j] <= valueData[comparator]) {
                        i++;
                        if(i != j){
                            std::cout << "Swapping " << "valueData[" << i << "] = " << valueData[i] << " and "
                                      << "valueData[" << j << "] = " << valueData[j] << "\n";
                            tmp = valueData[i];
                            //Swap(&swap1, &swap2);
                            valueData.replace(i, valueData[j]);
                            valueData.replace(j, tmp);
                            //swap(&arr[i], &arr[j]);
                            for(int k=0; k<arraySize; k++) {
                                std::cout << valueData[k] << "  " << std::flush;
                            }
                            std::cout << "\n";
                        }
                    }
                }
                tmp = valueData[i+1];
                //Swap(&swap1, &swap2);
                valueData.replace(i+1, valueData[comparator]);
                valueData.replace(comparator, tmp);
                //swap(&arr[i + 1], &arr[h]);
                return (i + 1);
        };
        int part = p();

        // Debugging
        // TODO: Remove when everything works
        std::cout << "Partitioned with: " << "valueData[" << part << "] = " << valueData[part] << "\n";
        for(int k=0; k<arraySize; k++) {
            std::cout << valueData[k] << "  " << std::flush;
        }
        std::cout << "\n---------------------------------------\n";

        // If there are elements on left side of pivot,
        // then push left side to stack
        if (part - 1 > selector) {
            tmpData[++counter] = selector;
            tmpData[++counter] = part - 1;
        }

        // If there are elements on right side of pivot,
        // then push right side to stack
        if (part + 1 < comparator) {
            tmpData[++counter] = part + 1;
            tmpData[++counter] = comparator;
        }
        updateGUI();
    }else {
        updateGUI();
        // Debugging
        // TODO: Replace with/add GUI message when everything works
        std::cout << "Final Result:" << std::endl;
        for(int k=0; k<arraySize; k++){
            std::cout << valueData[k] << " -> " << std::flush;
        }
        std::cout << ":D" << std::endl;
        // keep this one
        m_timer->stop();
    }

}

void Sorter::bubbleSort() {
    comparator = selector + 1;

    if (valueData[selector] > valueData[comparator]) {
        tmp = valueData[selector];
        //Swap(&swap1, &swap2);
        valueData.replace(selector, valueData[comparator]);
        valueData.replace(comparator, tmp);
    }
    updateGUI();

    // Checks if the sorting algorithm has passed through the inner loop, then the entire array
    if(selector < arraySize-counter-2){
        selector++;
    }else {
        selector=0;
        counter++;
        // Debugging
        // TODO: Remove when everything works
        for(int k=0; k<arraySize; k++) {
            std::cout << valueData[k] << "  " << std::flush;
        }
        std::cout << "\n";
        if(counter == arraySize-1) {
            // Debugging
            // TODO: Replace with/add GUI message when everything works
            std::cout << "Final Result:" << std::endl;
            for(int k=0; k<arraySize; k++){
                std::cout << valueData[k] << " -> " << std::flush;
            }
            std::cout << ":D" << std::endl;
            // keep this one
            m_timer->stop();
        }
    }
}

void Sorter::insertionSort() {
    if(!initialized) {
        comparator++;
        initialized = true;
    }

    tmp = valueData[comparator];
    selector = comparator - 1;

    while (selector >= 0 && valueData[selector] > tmp) {
        valueData[selector + 1] = valueData[selector];
        selector--;
    }

    valueData[selector + 1] = tmp;
    updateGUI();


    if(counter == arraySize-2) {
        // Debugging
        // TODO: Replace with/add GUI message when everything works
        std::cout << "Final Result:" << std::endl;
        for(int k=0; k<arraySize; k++){
            std::cout << valueData[k] << " -> " << std::flush;
        }
        std::cout << ":D" << std::endl;
        // keep this one
        m_timer->stop();
    }else{
        counter++;
        comparator++;
        // Debugging
        // TODO: Remove when everything works
        for(int k=0; k<arraySize; k++) {
            std::cout << valueData[k] << "  " << std::flush;
        }
        std::cout << "\n";
    }
}

void Sorter::heapSort() {
    // Building the max heap
    // TODO: figure out how/if this should be displayed
        // TODO: fix naming conventions
    if(!initialized) {
        std::cout << "Building max heap..\n";
        for (int i = 1; i < arraySize; i++) {
            // if child is bigger than parent
            if (valueData[i] > valueData[(i - 1) / 2]) {
                int j = i;

                // swap child and parent until
                // parent is smaller
                while (valueData[j] > valueData[(j - 1) / 2]) {
                    tmp = valueData[(j-1)/2];
                    //Swap(&swap1, &swap2);
                    valueData.replace((j-1)/2, valueData[j]);
                    valueData.replace(j, tmp);
                    j = (j - 1) / 2;
                }
            }
        }

        counter = arraySize - 1;
        initialized = true;

        std::cout << "Max heap:\n";
        // Debugging
        // TODO: Remove when everything works
        for(int k=0; k<arraySize; k++) {
            std::cout << valueData[k] << "  " << std::flush;
        }
        std::cout << "\n";
    }
    // swap value of first indexed with last indexed
    tmp = valueData[counter];
    //Swap(&swap1, &swap2);
    valueData.replace(counter, valueData[0]);
    valueData.replace(0, tmp);

    updateGUI();

    // maintaining heap property after each swap
    comparator = 0, selector = 1;

    // TODO: take out of loop, to be displayed (lav prio)
    while (selector < counter) {
        // if left child is smaller than right child point index variable to right child
        if (valueData[selector] < valueData[selector + 1] && selector < (counter - 1))
            selector++;

        // if parent is smaller than child then swapping parent with child having higher value
        if (valueData[comparator] < valueData[selector] && selector < counter) {
            tmp = valueData[selector];
            //Swap(&swap1, &swap2);
            valueData.replace(selector, valueData[comparator]);
            valueData.replace(comparator, tmp);
        }

        comparator = selector;
        selector = (2 * comparator + 1);

    }

    if(counter == 0) {
        // Debugging
        // TODO: Replace with/add GUI message when everything works
        std::cout << "Final Result:" << std::endl;
        for(int k=0; k<arraySize; k++){
            std::cout << valueData[k] << " -> " << std::flush;
        }
        std::cout << ":D" << std::endl;
        // keep this one
        m_timer->stop();
    }else{
        counter--;
        std::cout << "\n";
    }
}

void Sorter::mergeSort() {
    if(!initialized) {
        comparator = arraySize-1;
        tmpData = valueData;
        counter = 1;
        std::cout << "counter = " << counter << "\n";
        std::cout << "selector = " << selector << "\n";
        initialized = true;
    }
    // low = comparator, high = selector, counter = m?

    // divide the array into blocks of size m
    // counter = [1, 2, 4, 8, 16...]
    // for counter = 1, selector = 0, 2, 4, 6, 8
    // for counter = 2, selector = 0, 4, 8
    // for counter = 4, selector = 0, 8
    // ...
    std::cout << "selector = " << selector << " | ";
    int from = selector;
    int mid = selector + counter - 1;
    auto to = [=]() -> int {
        return (selector + 2*counter - 1 < comparator) ? selector + 2*counter - 1 : comparator;
    };


    // Merge two sorted subarrays valueData[from .. mid] and valueData[mid + 1 .. to]
    // TODO: fix naming conventions
    int tmpi = from, tmpk = from, tmpj = mid + 1;

    // loop till there are elements in the left and right runs
    while (tmpi <= mid && tmpj <= to()) {
        if (valueData[tmpi] < valueData[tmpj])
            tmpData[tmpk++] = valueData[tmpi++];
        else
            tmpData[tmpk++] = valueData[tmpj++];
    }

    // Copy remaining elements
    while (tmpi < arraySize && tmpi <= mid)
        tmpData[tmpk++] = valueData[tmpi++];

    // Don't need to copy second half
    // copy back to the original array to reflect sorted order
    for (int i = from; i <= to(); i++)
        valueData[i] = tmpData[i];

    updateGUI();

    // TODO: this currently runs an extra loop, see if this can be fixed
    if(selector <= comparator){
        selector += 2*counter;
    }else {
       selector = 0;
       counter = 2*counter;
       std::cout << "\ncounter = " << counter << "\n";
       std::cout<< "Merging...\n";
       // Debugging
       // TODO: Remove when everything works
       for(int k=0; k<arraySize; k++) {
           std::cout << valueData[k] << "  " << std::flush;
       }
       std::cout << "\n";
       if(counter >= comparator) {
              // Debugging
              // TODO: Replace with/add GUI message when everything works
              std::cout << "Final Result:" << std::endl;
              for(int k=0; k<arraySize; k++){
                  std::cout << valueData[k] << " -> " << std::flush;
              }
              std::cout << ":D" << std::endl;
              // keep this one
              m_timer->stop();
        }
    }
}

// TODO: see if there's ever going to be a need for a set of utility functions (lav prio)
/*
void Sorter::Swap(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}
*/
