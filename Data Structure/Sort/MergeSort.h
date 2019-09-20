#ifndef INC_233_MERGESORT_H
#define INC_233_MERGESORT_H

namespace Merge {

    template<class T> void MergeList(T*, int, int, int);
    template<class T> void MergeSort(T *a, int left, int right) {	//Merge Sort[left, right]

        if (left >= right) return;
        int mid = (left + right) >> 1;
        MergeSort(a, left, mid);	//sort 2 subsequence
		MergeSort(a, mid + 1, right);	
        MergeList(a, left, mid, right);	//& merge them
    }
    template<class T> void MergeList(T *a, int left, int mid, int right) {//merge 2 sorted sequence[left,mid][mid+1,right]

		int *res = new int[right - left + 1];	//allocate temporary memory
		int i = left, j = mid + 1, ct = 0;
		while (i <= mid and j <= right) {
			res[ct++] = (a[i] <= a[j]) ? a[i++] : a[j++];
		}
		while (i <= mid) res[ct++] = a[i++];
		while (j <= right) res[ct++] = a[j++];
        for (int i = 0; i < ct; i++) {
        	a[left + i] = res[i];
		}
        delete res;
    }
}

#endif //INC_233_MERGESORT_H
