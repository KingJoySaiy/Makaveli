#ifndef INC_233_INSERTIONSORT_H
#define INC_233_INSERTIONSORT_H

#include <algorithm>

namespace Insertion {        //Insertion Sort in Sequence

    template<class T> void Straight(T *a, int n) {	//Staright Insertion Sort

        for (int i = 0, j; i < n - 1; i++) {
            T tmp = a[i + 1];
            for (j = i; j >= 0 and a[j] > tmp; j--) {
                a[j + 1] = a[j];
            }
            a[j + 1] = tmp;
        }
    }

    template<class T> void Binary(T *a, int n) {	//Binary Insertion Sort
    
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

    template<typename T> void Shell(T *a, int n) {	//shell's Sort
        
        /*
        Shell increment : h = 1, 2, 4...[n / 2]
        Hibbard increment : h = 1, 3, 7...(2k + 1)
        Knuth increment : h = 1, 4, 13...(3k + 1) 
        */
		int h = 1;
        while (h < n / 3) h = 3 * h + 1;	//Knuth increment
        while (h >= 1) {
        	//0-h regarded as sorted
            for (int i = 0, j; i < n - h; i++) {
            	T tmp = a[i + h];
                for (j = i; j >= 0 and a[j] > tmp; j -= h) {
					a[j + h] = a[j];
                }
                a[j + h] = tmp;
            }
            h /= 3;
        }
    }
}

#endif //INC_233_INSERTIONSORT_H
