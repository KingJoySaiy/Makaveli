#ifndef INC_233_ARRAY_H
#define INC_233_ARRAY_H

#include <cstdarg>  //标准头文件，提供宏va_start, va_arg, 和 va_end
#include <cstdlib>
#include <iostream>

#define ERROR -1
#define OK 1
#define ElemType int
#define MAX_ARRAY_DIM 8 //假设数组的维数的最大值为8

using namespace std;

class Array {
private:
    ElemType *base;     //数组元素的基址
    int dim;            //数组的维数
    int *bounds;        //数组维界基址
    int *constants;     //数组映像函数常量基址
public:
    int InitArray(int dd, ...);   //若维数dim和随后的各维的长度合法，则构造相应的数组A
    int DestoryArray();            //销毁数组A
    int Value(ElemType &e, ...);   //A是n为数组，e为元素变量，随后是n个下标值，将下标值对应的元素赋给e
    int Assign(ElemType e, ...);   //将元素e赋给指定的下标值
    int Locate(va_list ap, int &off);  //返回指定的下标值对应的偏移地址， 存放在off
};

int Array::InitArray(int dd, ...) {
    
    if (dd < 1 || dd > MAX_ARRAY_DIM) return ERROR;
    this->dim = dd;
    this->bounds = (int *) malloc(dd * sizeof(int));
    if (!this->bounds) return ERROR;

    int elemtotal = 1;
    va_list ap;
    va_start(ap, dd);  //获取存放变长参数信息的数组
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
    //开始求映像数组
    //int L = sizeof(ElemType);//每一个元素的大小
    int L = 1;//注意这里的元素的单位大小就是 1， 因为 A.base + off 实际上是 A.base+off*sizeof(ElemType);
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
    A.InitArray(3, 3, 2, 3);    //3维数组，每一维长度为3,2,3
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
#undef MAX_ARRAY_DIM //假设数组的维数的最大值为8

#endif //INC_233_ARRAY_H
