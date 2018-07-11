#ifndef INC_233_SELECTIONSORT_H
#define INC_233_SELECTIONSORT_H

#include <algorithm>

namespace Selection {

    template<class T> class Heap;
    template<class T> void HeapSort(T *a, int n);
    const int maxn = int(1e4);

    template<class T> class Heap {          //堆的基本实现
    private:
        T data[maxn];
        int size = 0;
        void push (T x) {
            int i = size++;
            while (i > 0) {
                int p = (i - 1) / 2;        //父节点编号
                if (data[p] <= x) break;    //若大小不颠倒则退出
                data[i] = data[p];          //取下父节点，自己往上提
                i = p;
            }
            data[i] = x;
        }
        T pop() {
            T res = data[0], x = data[--size];
            int i = 0;
            while (i * 2 + 1 < size) {
                int a = 2 * i + 1, b = 2 * i + 2;   //比较子节点的值
                if (b < size and data[b] < data[a]) a = b;
                if (data[a] >= x) break;    //若不大小颠倒则退出
                data[i] = data[a];
                i = a;
            }
            data[i] = x;
            return res;
        }
        friend void HeapSort<>(T*, int);
    };

    template<class T> void Selection(T *a, int n) {     //选择排序

        for (int i = 0; i < n - 1; i++) {
            int id = i;
            for (int j = i + 1; j < n; j++) {
                if (a[j] < a[id]) id = j;
            }
            std::swap(a[i], a[id]);
        }
    }

    template<class T> void HeapSort(T *a, int n) {         //堆排序

        Heap<T> heap;
        for (int i = 0; i < n; i++) heap.push(a[i]);
        for (int i = 0; i < n; i++) a[i] = heap.pop();
    }
}

#endif //INC_233_SELECTIONSORT_H
