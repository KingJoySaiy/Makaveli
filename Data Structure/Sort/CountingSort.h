#ifndef INC_233_COUNTINGSORT_H
#define INC_233_COUNTINGSORT_H

#include <climits>
#include <algorithm>

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
    
    const int bucketNum = 10;	//define 10 buckets
    
    template<class T> void BucketArray(T *a, int n) {	//Bucket Sort + Bubblle Sort(array)
    	
    	int base = INT_MAX, back = INT_MIN, id = 0;
		for (int i = 0; i < n; i++) {	//range [base, back]
			if (a[i] < base) base = a[i];
			if (a[i] > back) back = a[i];
		}
		T **p = new int*[bucketNum];	//initialize buckets
		for (int i = 0; i < bucketNum; i++) {
			p[i] = new int[n];
		}
		int ct[bucketNum] = {0}, range = (back - base + 1) / bucketNum + 1;	//count & range of each bucket
		
		for (int i = 0; i < n; i++) {
			int tmp = (a[i] - base) / range;
			p[tmp][ct[tmp]++] = a[i];
		}
		for (int k = 0; k < bucketNum; k++) {	//sort every buckey by BubbleSort
			for (int i = 0; i < ct[k]; i++) {
				for (int j = i; j > 0; j--) {
					if (p[k][j - 1] > p[k][j]) std::swap(p[k][j - 1], p[k][j]);
				}
			}
			for (int i = 0; i < ct[k]; i++) {
				a[id++] = p[k][i];
			}
		}
	}
	
	template<class T> void BucketList(T *a, int n) {	//Bucket Sort + Straight Insertion Sort(list)
    	
    	
	}
	
	template<class T> void Radix(T *a, int n) {		//Radix Sort
		
		
	}
}

#endif //INC_233_COUNTINGSORT_H
