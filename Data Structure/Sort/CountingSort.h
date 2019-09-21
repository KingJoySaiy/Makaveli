#ifndef INC_233_COUNTINGSORT_H
#define INC_233_COUNTINGSORT_H

#include <climits>

namespace Counting {

    template<class T> void CountingSort(T *a, int n) {	//Counting Sort

		int base = INT_MAX, back = INT_MIN, ct = 0;
		for (int i = 0; i < n; i++) {	//range [base, back]
			if (a[i] < base) base = a[i];
			if (a[i] > back) back = a[i];
		}
		
        T *b = new T[back - base + 1];
		memset(b, 0, sizeof(int) * (back - base + 1));
        
        for (int i = 0; i < n; i++) {
        	b[a[i] - base]++;	//count
		}
		for (int i = 0; i <= back - base; i++) {
			while (b[i]--) {
				a[ct++] = base + i;
			}
		}
		delete b;
    }
    
    template<class T> void Bucket(T *a, int n) {	//Bucket Sort
    	
    	
	}
	
	template<class T> void Radix(T *a, int n) {		//Radix Sort
		
		
	}
}

#endif //INC_233_COUNTINGSORT_H
