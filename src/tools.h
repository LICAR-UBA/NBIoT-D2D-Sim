#ifndef TOOLS_H_
#define TOOLS_H_

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h> 
#include <math.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <sched.h>
#include "pcg_basic.h"
#include "parameters.h"

/*--- Workload structure: Index and offset -----------------------------------*/
struct workload
{
    int quota;
    int begin;
};

extern struct workload * w_load;

/*--- Calculating workload distribution --------------------------------------*/
void workload(struct workload * w_load, int n_threads, int no_topologies);

/*--- Random number between min and max --------------------------------------*/
long double rnd(long double min, long double max, int thread_index);

/*--- Generate exponentially distributed random variables --------------------*/
double expon( double l, int thread_index );

/*--- Distance function ------------------------------------------------------*/
double distance( double x1, double x2, double y1, double y2 );

/*--- Quick sort -------------------------------------------------------------*/
/*--- https://www.geeksforgeeks.org/quick-sort/ ------------------------------*/

/*--- A utility function to swap two elements --------------------------------*/
void swap( int* a, int* b );

/*--- This function takes last element as pivot, places the pivot element at its 
   correct position in sorted array, and places all smaller (smaller than 
   pivot) to left of pivot and all greater elements to right of pivot --------*/
int partition( int * arr1, int * arr2, int low, int high ); 
  
/*--- The main function that implements QuickSort 
                    arr[] --> Array to be sorted, 
                    low  --> Starting index, 
                    high  --> Ending index -----------------------------------*/
void quick_sort( int * arr1, int * arr2, int low, int high );

void calc_no_relays(int * no_relays_by_bs_due );

extern pcg32_random_t * nums_random;

#endif
