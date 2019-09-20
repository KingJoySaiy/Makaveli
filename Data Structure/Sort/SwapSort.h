#ifndef INC_233_SWAPSORT_H
#define INC_233_SWAPSORT_H

#include <algorithm>

namespace Swap {

    template<class T> void Bubble(T *a, int n) {    //Bubble Sort

        for (int i = 0; i < n; i++) {
            for (int j = i; j > 0; j--) {
                if (a[j - 1] > a[j]) std::swap(a[j], a[j - 1]);
            }
        }
    }

    template<class T> void Quick(T *a, int left, int right) {     //Quick Sort[left-right]

        if (left >= right) return;
        int i = left, j = right;
        T tmp;
        while (i < j) {
            tmp = a[i];
            while (i < j and a[j] >= tmp) j--;
            a[i] = a[j];
            while (i < j and a[i] <= tmp) i++;
            a[j] = a[i];
            a[i] = tmp;
        }
        Quick(a, left, i - 1);
        Quick(a, i + 1, right);
    }
}

#endif //INC_233_SWAPSORT_H
