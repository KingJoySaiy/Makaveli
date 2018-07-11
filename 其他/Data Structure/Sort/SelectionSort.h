#ifndef INC_233_SELECTIONSORT_H
#define INC_233_SELECTIONSORT_H

#include <algorithm>

namespace Selection {

    template<class T> void Selection(T *a, int n) {     //选择排序

        for (int i = 0; i < n - 1; i++) {
            int id = i;
            for (int j = i + 1; j < n; j++) {
                if (a[j] < a[id]) id = j;
            }
            std::swap(a[i], a[id]);
        }
    }

    template<class T> void Heap(T *a, int n) {         //堆排序

        
    }
}

#endif //INC_233_SELECTIONSORT_H
