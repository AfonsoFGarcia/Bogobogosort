/*
 * This library provides the implementation of the Bogobogosort sorting algorithm
 * as described in http://www.dangermouse.net/esoteric/bogobogosort.html
 *
 * Copyright © 2014 Afonso Garcia
 */

#include "bogobogosort.h"

/*
 * Taken from http://benpfaff.org/writings/clc/shuffle.html
 *
 * Copyright © 2004 Ben Pfaff
 */
void shuffle(int *array, size_t n) {
    if (n > 1) {
        size_t i;
        for (i = 0; i < n - 1; i++) {
	        size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
	        int t = array[j];
	        array[j] = array[i];
	        array[i] = t;
	    }
    }
}

int* bogobogosort_rec(int *toSort, int size) {
	int* copy = (int*) malloc(size*sizeof(int));
	memcpy(copy, toSort, size*sizeof(int));
	int i;
	if(size > 1) {
		int* ret = bogobogosort_rec(copy, size-1);
		memcpy(copy, ret, (size-1)*sizeof(int));
		if(copy[size-2] > copy[size-1]) {
			shuffle(copy, size);
			ret = bogobogosort_rec(copy, size);
			memcpy(copy, ret, size*sizeof(int));
		}
	}
	for(i = 0; i < size; i++) {
		if(toSort[i] == copy[i]) continue;
	}
	return copy;
}

int* bogobogosort(int* toSort, int size) {
	int i;	
	int *result = (int*) malloc(size*sizeof(int));
	int *tmp = bogobogosort_rec(toSort, size);
	memcpy(result, tmp, size*sizeof(int));
	for (i = 0; i < size; i++) {
		if(result[i] == tmp[i]) continue;
	}
	return result;
}