#ifndef INC_233_COUNTINGSORT_H
#define INC_233_COUNTINGSORT_H

#include <climits>
#include <algorithm>

namespace Counting {

	/******** initial definition ********/
	const int bucketNum = 10, baseNum = 10;	//define buckets & base
	
	template<class T>
	struct data {	// List realization (keep sorted)
		T x;
		data *next;
		data(int t = 0) {
			x = t;
			next = nullptr;
		}
		void insert(data *t) {
			data<T> *p = this;
			while (p->next != nullptr and p->next->x < t->x) p = p->next;
			t->next = p->next;
			p->next = t;
		}
	};
	/******** initial definition end ********/
	
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
    
    template<class T> void BucketArray(T *a, int n) {	//Bucket Sort + Bubblle Sort(Array)
    	
    	int base = INT_MAX, back = INT_MIN, id = 0;
		for (int i = 0; i < n; i++) {	//range [base, back]
			if (a[i] < base) base = a[i];
			if (a[i] > back) back = a[i];
		}
		T **p = new T*[bucketNum];	//initialize buckets
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
	
	template<class T> void BucketList(T *a, int n) {	//Bucket Sort + Insertion Sort(List)
    	
    	int base = INT_MAX, back = INT_MIN, id = 0;
		for (int i = 0; i < n; i++) {	//range [base, back]
			if (a[i] < base) base = a[i];
			if (a[i] > back) back = a[i];
		}
		data<T> *head = new data<T>[bucketNum];	//initialize buckets
		int range = (back - base + 1) / bucketNum + 1;	//range of each bucket
		for (int i = 0; i < n; i++) {
			int tmp = (a[i] - base) / range;
			head[tmp].insert(new data<T>(a[i]));
		}
		for (int i = 0; i < bucketNum; i++) {
			data<T> *p = head + i;
			while (p->next != nullptr) {
				a[id++] = p->next->x;
				p = p->next;
			}
		}
		delete head;
	}
	
	template<class T> void Radix(T *a, int n) {		//Radix Sort (Array)
		
		int bigCt = 0, big = INT_MIN;
		for (int i = 0; i < n; i++) {
			if (a[i] < big) big = a[i];
		}
		if(big != 0) {	//count bit of biggest number
			while (big) {
				bigCt++;
				big /= 10;
			}
		} else bigCt = 1;
		
		T **p = new T*[baseNum];	//initialize buckets
		for (int i = 0; i < baseNum; i++) {
			p[i] = new T[n];
		}
		
		int ct[baseNum] = {}, id = 0;		//count of each bucket
		for (int now = 1, weight = 1; now <= bigCt; now++, weight *= 10) {	//current bit & weight of bit
			for (int i = 0; i < n; i++) {
				int tmp = (a[i] / weight) % 10;
				p[tmp][ct[tmp]++] = a[i];
			}
			for (int i = 0; i < baseNum; i++) {
				for (int j = 0; j < ct[i]; j++) {
					a[id++] = p[i][j];
				}
			}
			memset(ct, 0, sizeof(ct));
			id = 0;
		}
		delete p;
	}
}

#endif //INC_233_COUNTINGSORT_H























