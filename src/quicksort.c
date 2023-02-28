#include <stdio.h>
#include <string.h>
#include "quicksort.h"

/* Static (private to this file) function prototypes. */
static void swap(void *a, void *b, size_t size);
static int lomuto(void *array, int left, int right, size_t elem_sz,
                  int (*cmp) (const void*, const void*));
static void quicksort_helper(void *array, int left, int right, size_t elem_sz,
                             int (*cmp) (const void*, const void*));

/**
 * Swaps the values in two pointers.
 *
 * Casts the void pointers to type (char *) and works with them as char pointers
 * for the remainder of the function. Swaps one byte at a time, until all 'size'
 * bytes have been swapped. For example, if ints are passed in, size will be 4
 * and this function will swap 4 bytes starting at a and b pointers.
 */
static void swap(void *a, void *b, size_t size) {
	char *a1 = (char*)a;
	char *b1 = (char*)b;
	char temp;
	for (int i = 0; i < size; i++){
		temp = *(a1 + i); //equivalent to temp = a1[i]
	       	*(a1 + i) = *(b1 + i);	
		*(b1 + i) = temp;
	}
}

/**
 * Partitions array around a pivot, utilizing the swap function. Each time the
 * function runs, the pivot is placed into the correct index of the array in
 * s\
 * orted order. All elements less than the pivot should be to its left, and all
 * elements greater than or equal to the pivot should be to its right.
 */
static int lomuto(void *array, int left, int right, size_t elem_sz,
                  int (*cmp) (const void*, const void*)) {
	char *temp = (char *)array;
	void *x = (void*)(temp + left * elem_sz); //equivalent to array[left]
	int s = left;
	for (int j = left + 1; j <= right; j++) {
		void *cur = (void *)(temp + j * elem_sz);
		if (cmp(cur, x) < 0) {
			s++;
			void *str_p = (void*)(temp + s * elem_sz);
			swap(str_p, cur, elem_sz);
		}
	}
	void *str_p = (void *)(temp + s * elem_sz);
	swap(str_p, x, elem_sz);
	return s;
}

/**
 * Sorts with lomuto partitioning, with recursive calls on each side of the
 * pivot.
 * This is the function that does the work, since it takes in both left and
 * right index values.
 */
static void quicksort_helper(void *array, int left, int right, size_t elem_sz,
		int (*cmp) (const void*, const void*)){

	if (left < right) {
		int q = lomuto(array, left, right, elem_sz, cmp);
		quicksort_helper(array, left, q - 1, elem_sz, cmp);
		quicksort_helper(array, q + 1, right, elem_sz, cmp);
	}
}

/**
 * Quicksort function exposed to the user.
 * Calls quicksort_helper with left = 0 and right = len - 1.
 */
void quicksort(void *array, size_t len, size_t elem_sz,
               int (*cmp) (const void*, const void*)) {
		quicksort_helper(array, 0, len - 1, elem_sz, cmp);
}

/**
 * Compares two integers passed in as void pointers and returns an integer
 * representing their ordering.
 * First casts the void pointers to int pointers.
 * Returns:
 * -- 0 if the integers are equal
 * -- 1 if the first integer is greater
 * -- -1 if the second integer is greater
 */
int int_cmp(const void *a, const void *b) {
	int a1 = *(const int*)a;
	int b1 = *(const int*)b;

	if (a1 < b1) {
		return -1;
	} else if (a1 > b1) {
		return 1;
	}else {
		return 0;
	}
}

/**
 * Compares two doubles passed in as void pointers and returns an integer
 * representing their ordering.
 * First casts the void pointers to double pointers.
 * Returns:
 * -- 0 if the doubles are equal
 * -- 1 if the first double is greater
 * -- -1 if the second double is greater
 */
int dbl_cmp(const void *a, const void *b){
	double a1 = *(const double*)a;
	double b1 = *(const double*)b;
	if (a1 < b1) {
		return -1;
	} else if (a1 > b1) {
		return 1;
	} else {
		return 0;
	}
}

/**
 * Compares two char arrays passed in as void pointers and returns an integer
 * representing their ordering.
 * First casts the void pointers to char* pointers (i.e. char **).
 * Returns the result of calling strcmp on them.
 */
int str_cmp(const void *a, const void *b) {  
	const char* a1 = *(const char**)a;
	const char* b1 = *(const char**)b;
	return strcmp(a1, b1);
}

