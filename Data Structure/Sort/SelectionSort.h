#ifndef INC_233_SELECTIONSORT_H
#define INC_233_SELECTIONSORT_H

#include <algorithm>

namespace Selection {

    template<class T> class Heap;
    template<class T> void HeapSort(T *a, int n);
    const int maxn = int(1e4 + 5);

    template<class T> class Heap {          //realization of heap(minimun root)
    private:
        T data[maxn];
        int size = 0;
        void push (T x) {
            int i = size++;
            while (i > 0) {
                int p = (i - 1) / 2;        //father node of 'i'
                if (data[p] <= x) break;    //break when sorted
                data[i] = data[p];          //set father node(raise 'x')
                i = p;
            }
            data[i] = x;
        }
        T pop() {
            T res = data[0], x = data[--size];
            int i = 0;
            while (i * 2 + 1 < size) {
                int a = 2 * i + 1, b = 2 * i + 2;   //compare 2 children node
                if (b < size and data[b] < data[a]) a = b;
                if (data[a] >= x) break;    //break when sorted
                data[i] = data[a];
                i = a;
            }
            data[i] = x;
            return res;
        }
        friend void HeapSort<>(T*, int);
    };

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

        Heap<T> heap;
        for (int i = 0; i < n; i++) heap.push(a[i]);
        for (int i = 0; i < n; i++) a[i] = heap.pop();
    }
}

#endif //INC_233_SELECTIONSORT_H
