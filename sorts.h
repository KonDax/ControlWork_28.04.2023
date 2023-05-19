#ifndef _sorts_h_
#define _sorts_h_

#include <chrono>
#include <cstring>
#include "arraywork.h"

void bubble_sort(int*, int);
void insertion_sort(int*, int);
void selection_sort(int*, int);
void count_sort(int*, int);
void quickSort(int*, int);
void merge(int*, int, int);
void mergeSort(int* ar, int size);

class Sorts{
	private:
		void (*sortF[6])(int*, int) {bubble_sort, insertion_sort, selection_sort, count_sort, quickSort, mergeSort};
	public:
		int get_time_ms(void (*)(int*, int), int);
		auto getSortById(int i){return sortF[i];}
};

#endif
