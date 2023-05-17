#include "arraywork.h"

void swap(int& a, int& b){
    int c = a;
    a = b;
    b = c;
}

int get_max(const int* ar, int size){
    if (size == 1){
        return ar[0];
    }
    int maxx = get_max(ar, --size);
    if (ar[size-1] > maxx)
        return ar[size-1];
    return maxx;
}

int get_min(const int* ar, int size){
    if (size == 1){
        return ar[0];
    }
    int minn = get_min(ar, --size);
    if (ar[size-1] < minn)
        return ar[size-1];
    return minn;
}


void random_Fill_ar(int* ar, int size, int min, int max){
    srand(clock());
    for (int i = 0; i < size; i++){
        ar[i] = min + rand() % (max - min + 1);
    }
}

void show_ar(int* ar, int size, char element){
    for (int i = 0; i < size; i++){
        std::cout << ar[i] << element;
    }
    std::cout << std::endl;
}

