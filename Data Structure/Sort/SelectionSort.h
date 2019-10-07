#ifndef INC_233_SELECTIONSORT_H
#define INC_233_SELECTIONSORT_H

#include <algorithm>
#include "../../Fundamental/Heap.h"

namespace Selection {

    template<class T> void Selection(T *a, int n) {     //Selection Sort

        for (int i = 0; i < n - 1; i++) {
            int id = i;
            for (int j = i + 1; j < n; j++) {
                if (a[j] < a[id]) id = j;
            }
            std::swap(a[i], a[id]);
        }
    }

    template<class T> void HeapSort(T *a, int n) {         //Heap Sort

        minHeap<T> heap;
        for (int i = 0; i < n; i++) heap.push(a[i]);
        for (int i = 0; i < n; i++) a[i] = heap.pop();
    }
}

#endif //INC_233_SELECTIONSORT_H
