#ifndef INC_233_MERGESORT_H
#define INC_233_MERGESORT_H

namespace Merge {

    template<class T> T* MergeList(T*, int, T*, int);
    template<class T> T* MergeSort(T *a, int n) {       //归并排序（结果另开内存）

        if (n <= 1) return a;
        int mid = n >> 1;
        T *left = MergeSort(a, mid), *right = MergeSort(a + mid, n - mid);
        T *res = MergeList(left, mid, right, n - mid);
        delete left; delete right;
        return res;
    }
    template<class T> T* MergeList(T *left, int n, T *right, int m) {   // 合并2个有序序列

        if (n == 0) return right;
        if (m == 0) return left;
        T *res = new T[n + m];
        int ct = 0;
        while (n > 0 and m > 0) {
            if (left[0] <= right[0]) {
                res[ct++] = left[0];
                left++; n--;
            } else {
                res[ct++] = right[0];
                right++; m--;
            }
        }
        while (n--) res[ct++] = *(left++);
        while (m--) res[ct++] = *(right++);
        return res;
    }
}

#endif //INC_233_MERGESORT_H
