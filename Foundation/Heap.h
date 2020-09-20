#ifndef INC_233_HEAP_H
#define INC_233_HEAP_H

#define maxn 10005

/******** minimum heap ********/
template<class T> class minHeap {
private:
    T data[maxn];
    int size = 0;
public:
    void push (T x) {	//push x into the heap
        int i = size++;
        while (i > 0) {
            int p = (i - 1) / 2;        //father node of 'i'
            if (data[p] <= x) break;    //break when sorted
            data[i] = data[p];          //set father node(raise 'x')
            i = p;
        }
        data[i] = x;
    }
    T top() {	//get the top of the heap
    	return data[0];
	} 
    T pop() {	//pop the top out of the heap
        T res = data[0], x = data[--size];
        int i = 0;
        while (i * 2 + 1 < size) {
            int a = 2 * i + 1, b = 2 * i + 2;   //compare 2 children node & select the smaller one
            if (b < size and data[b] < data[a]) a = b;
            if (data[a] >= x) break;    //break when sorted
            data[i] = data[a];	//move a up, update i
            i = a;
        }
        data[i] = x;
        return res;
    }
};


/******** maximum heap ********/
template<class T> class maxHeap {
private:
    T data[maxn];
    int size = 0;
public:
    void push (T x) {	//push x into the heap
        int i = size++;
        while (i > 0) {
            int p = (i - 1) / 2;
            if (data[p] >= x) break;	//(different from minimum heap)
            data[i] = data[p];
            i = p;
        }
        data[i] = x;
    }
    T top() {	//get the top of the heap
    	return data[0];
	} 
    T pop() {	//pop the top out of the heap
        T res = data[0], x = data[--size];
        int i = 0;
        while (i * 2 + 1 < size) {
            int a = 2 * i + 1, b = 2 * i + 2;
            if (b < size and data[b] > data[a]) a = b;	//(different)
            if (data[a] <= x) break;	//(different)
            data[i] = data[a];
            i = a;
        }
        data[i] = x;
        return res;
    }
};

#undef maxn

#endif //INC_233_HEAP_H
