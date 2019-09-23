#ifndef INC_233_ARRAY_H
#define INC_233_ARRAY_H

#include <cstdarg>  //support va_start, va_arg, va_end & other macros
#include <cstdlib>
#include <iostream>

#define ERROR -1
#define OK 1
#define ElemType int
#define MAX_ARRAY_DIM 8 //define max dimension is 8

using namespace std;

class Array {
private:
    ElemType *base;     //base address
    int dim;            //dimension of array
    int *bounds;        //length of each dimension
    int *constants;     //constant data  for mapping
public:
    int InitArray(int dd, ...);   //construct array-a when dim and length of each dimension are valid
    int DestoryArray();            //Destroy array-a
    int Value(ElemType &e, ...);   //set e as value of (i, j, k...)
    int Assign(ElemType e, ...);   //set value of (i, j, k....) as e
    int Locate(va_list ap, int &off);  //set offset address of (i, j, k...) to off
};

int Array::InitArray(int dd, ...) {
    
    if (dd < 1 || dd > MAX_ARRAY_DIM) return ERROR;
    this->dim = dd;
    this->bounds = (int *) malloc(dd * sizeof(int));
    if (!this->bounds) return ERROR;

    int elemtotal = 1;
    va_list ap;
    va_start(ap, dd);
    for (int i = 0; i < dd; ++i) {
        this->bounds[i] = va_arg(ap, int);
        if (this->bounds[i] < 0) return ERROR;
        elemtotal *= this->bounds[i];
    }
    va_end(ap);
    this->base = (ElemType *) malloc(elemtotal * sizeof(ElemType));
    if (!this->base) return ERROR;
    this->constants = (int *) malloc(dd * sizeof(int));
    if (!this->constants) return ERROR;
    //calculate array-constants
    //int L = sizeof(ElemType);	//size of each element
    int L = 1;
    this->constants[dd - 1] = L;
    for (int i = dd - 2; i >= 0; --i)
        this->constants[i] = this->bounds[i + 1] * this->constants[i + 1];
    return OK;
}

int Array::DestoryArray() {
    
    if (!this->base) return ERROR;
    free(this->base);
    if (!this->bounds) return ERROR;
    free(this->bounds);
    if (!this->constants) return ERROR;
    free(this->constants);
    return OK;
}

int Array::Value(ElemType &e, ...) {
    
    va_list ap;
    int off;
    va_start(ap, e);
    if (this->Locate(ap, off) == ERROR) return ERROR;
    e = *(this->base + off);
    va_end(ap);
    return OK;
}

int Array::Assign(ElemType e, ...) {
    
    va_list ap;
    int off;
    va_start(ap, e);
    if (Locate(ap, off) == ERROR) return ERROR;
    *(this->base + off) = e;
    va_end(ap);
    return OK;
}

int Array::Locate(va_list ap, int &off) {
    
    off = 0;
    for (int i = 0; i < this->dim; ++i) {
        int ind = va_arg(ap, int);
        if (ind < 0 || ind >= this->bounds[i]) return ERROR;
        off += this->constants[i] * ind;
    }
    return OK;
}

void test() {

    Array A{};
    A.InitArray(3, 3, 2, 3);    //3 arrays, length of each dimension is (3,2,3)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 3; k++) {
                A.Assign(i + j + k, i, j, k);
            }
        }
    }
    for (int i = 0, tmp; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 3; k++) {
                A.Value(tmp, i, j, k);
                cout << tmp << " \n"[k == 2];
            }
            if (j == 1) cout << endl;
        }
    }
    A.DestoryArray();
}

#undef ERROR
#undef OK
#undef ElemType
#undef MAX_ARRAY_DIM

#endif //INC_233_ARRAY_H
