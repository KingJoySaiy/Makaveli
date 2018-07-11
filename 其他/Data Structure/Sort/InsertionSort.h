#ifndef INC_233_INSERTIONSORT_H
#define INC_233_INSERTIONSORT_H

#include <algorithm>

namespace Inertion {        //Insertion Sort in Sequence

    template<class T> void Straight(T *a, int n) {    //直接插入排序

        for (int i = 0, j; i < n - 1; i++) {
            T tmp = a[i + 1];
            for (j = i; ~j and a[j] > tmp; j--) {
                a[j + 1] = a[j];
            }
            a[j + 1] = tmp;
        }
    }

    template<class T> void Binary(T *a, int n) {      //折半插入排序

        for (int i = 1; i < n; i++) {
            if (a[i] < a[i - 1]) {
                T tmp = a[i];
                int low = 0, high = i - 1, mid;
                while (low <= high) {
                    mid = (low + high) >> 1;
                    if (a[mid] < tmp) low = mid + 1;
                    else high = mid - 1;
                }
                for (int j = i; j > low; j--) {
                    a[j] = a[j - 1];
                }
                a[low] = tmp;
            }
        }
    }

    template<typename T> void Shell(T *a, int n) { //希尔排序
        
        int h = 1;
        while (h < n / 3) h = 3 * h + 1;
        while (h >= 1) {
            for (int i = h; i < n; i++) {
                for (int j = i; j >= h and a[j] < a[j - h]; j -= h) {
                    std::swap(a[j], a[j - h]);
                }
            }
            h /= 3;
        }
    }
}

#endif //INC_233_INSERTIONSORT_H
