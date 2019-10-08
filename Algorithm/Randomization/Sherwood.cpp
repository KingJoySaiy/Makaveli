#include <bits/stdc++.h>
#include "../../Fundamental/Random.h"

using namespace std;

const int maxn =  105;
const int inf = INT_MAX / 2;
RandomNumber Rand;	//used to generate random numbers

/******** quick sort ********/
void quickSort(int a[], int left, int right) {     //Quick Sort[left, right]

    if (left >= right) return;
    int i = left, j = right, tmp, id = Rand.Random(j - i + 1) + i;
    swap(a[id], a[left]);	//select random id as the datum
    while (i < j) {
        tmp = a[i];
        while (i < j and a[j] >= tmp) j--;
        a[i] = a[j];
        while (i < j and a[i] <= tmp) i++;
        a[j] = a[i];
        a[i] = tmp;
    }
    quickSort(a, left, i - 1);
    quickSort(a, i + 1, right);
}
void quickSortTest() {
	
	int a[maxn], n = 10;
	cout << "initial array: ";
	for (int i = 0; i < n; i++) {	//initialize the array by random numbers
		cout << (a[i] = Rand.Random(100)) << " \n"[i == n - 1];
	}
//	shuffle(a, n);		//2nd Sherwood optimize: shuffle the array before sort it
	quickSort(a, 0, n - 1);
	cout << "sorted array: ";
	for (int i = 0; i < n; i++) {
		cout << a[i] << " \n"[i == n - 1];
	}
}


/******** find k-th smallest number ********/
int findK(int a[], int l, int r, int k) {	//range from l to r
	
	if (l == r) return a[l];
    int i = l, j = r, tmp, id = Rand.Random(j - i + 1) + i;	//same as above
    swap(a[id], a[l]);
    while (i < j) {		//once quick-sort
        tmp = a[i];
        while (i < j and a[j] >= tmp) j--;
        a[i] = a[j];
        while (i < j and a[i] <= tmp) i++;
        a[j] = a[i];
        a[i] = tmp;
    }
    tmp = i - l + 1;	//[l, i] <= [i + 1, r]
    if (k <= tmp) return findK(a, l, i, k);
    return findK(a, i + 1, r, k - tmp);
}
void findKTest() {	//test function
	
	int a[10] = {5, 0, 6, 9, 8, 4, 3, 7, 2, 1}, n = 10, k = 5;
//	shuffle(a, n);		//2nd Sherwood optimize: shuffle the array before sort it
	cout << k << "-th smallest number of the array: " << findK(a, 0, n - 1, 5) << endl;
	cout << "the sequence after find " << k << ": ";
	for (int i = 0; i < n; i++) {
		cout << a[i] << " \n"[i == n - 1];
	}
}


/******** main ********/ 
int main() {
	
	quickSortTest();
	findKTest();
	
	return 0;
} 
