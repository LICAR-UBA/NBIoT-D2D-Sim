#include "tools.h"

/*--- Workload distribution: index and offset --------------------------------*/

void workload(struct workload * w_load, int n_threads, int topologies)
{
    for (int i = 0; i < n_threads; i++)
    {
        w_load[i].quota = 0;
        w_load[i].begin = 0;
    }
    int j = 0;
    for (int i = 0; i < topologies; i++)
    {
        w_load[j].quota++;
        j++;
        if ( j == n_threads )
            j = 0;
    }
    int offset = 0;
    for (int i = 0; i < n_threads; i++)
    {
        w_load[i].begin = offset;
        offset += w_load[i].quota;
    }
}

/*--- Rand between min and max -----------------------------------------------*/

long double rnd( long double min, long double max, int thread_index )
{
    return ( max - min ) * ( pcg32_random_r( &nums_random[thread_index] )
                                             / (long double) UINT32_MAX ) + min;
}

/*--- Generate exponentially distributed random variables --------------------*/

double expon( double l, int thread_index )
{
    return -log( 1 - rnd( 0, 1, thread_index ) ) / l;
}

/*--- Distance function ------------------------------------------------------*/

double distance( double x1, double x2, double y1, double y2 )
{
    return sqrt( pow(x1 - x2, 2) + pow(y1 - y2, 2) );
}

/*--- Quick sort -------------------------------------------------------------*/
/* https://www.geeksforgeeks.org/quick-sort/ */

/* A utility function to swap two elements  */
void swap( int* a, int* b )
{
    int t = *a;
    *a = *b;
    *b = t;
}

/*--- This function takes last element as pivot, places 
      the pivot element at its correct position in sorted 
      array, and places all smaller (smaller than pivot) 
      to left of pivot and all greater elements to right 
      of pivot -------------------------------------------*/
int partition(int * arr1, int * arr2, int low, int high)
{
    int pivot = arr1[high]; /*--- pivot --*/
    int i = (low - 1); /*--- Index of smaller element --*/

    for (int j = low; j <= high - 1; j++)
    {
        /*--- If current element is smaller than the pivot --*/
        if ( arr1[j] < pivot )
        {
            i++;    /*--- Increment index of smaller element --*/
            swap( &arr1[i], &arr1[j] );
            swap( &arr2[i], &arr2[j] );
        }
    }
    swap(&arr1[i + 1], &arr1[high]);
    swap(&arr2[i + 1], &arr2[high]);
    return (i + 1);
}

/*--- The main function that implements QuickSort 
     arr[] --> Array to be sorted, 
     low  --> Starting index, 
     high  --> Ending index ---------------------*/

void quick_sort(int * arr1, int * arr2, int low, int high)
{
    if (low < high)
    {
        /*--- p_i is partitioning index, arr[p] is now at right place --------*/
        int p_i = partition(arr1, arr2, low, high); 

        /*--- Separately sort elements before partition and after partition --*/
        quick_sort(arr1, arr2, p_i + 1, high); 
    }
}

/*--- Calculate No of relays per base station since density of ues in
      intersection areas of foot prints: BS and DUE --------------------------*/
void calc_no_relays(int * relays)
{
    int bs_r[] = _bs_r;
    int due_r = _due_r;
    int bs_x[] = _bs_x;
    int due_x = _due_x;
    int bs_y[] = _bs_y;
    int due_y = _due_y;

    for (int bs = 0; bs < _no_bs; bs++)
    {
         /*--- Calculating intersection areas --------------------------------*/
         double d = distance( bs_x[bs], due_x, bs_y[bs] , due_y );
         double axis_x = (pow(bs_r[bs],2)-pow(due_r,2)+pow(d,2))/(2*d);
         double axis_y = sqrt(pow(bs_r[bs],2)-pow(axis_x,2));
         double circular_sector_1 = (atan(axis_y/axis_x)*pow(bs_r[bs],2));
         double circular_sector_2 = (atan(axis_y/(d-axis_x))*pow(due_r,2));
         double triangle_area_1 = axis_y * axis_x;
         double triangle_area_2 = axis_y * (d - axis_x);
         double total_area = ((circular_sector_1 - triangle_area_1) + 
                             (circular_sector_2 - triangle_area_2));
         double density = _no_ues_bs / (_pi * pow(bs_r[bs],2));
         int no_relays = (int) (density * total_area);
         relays[bs] = no_relays;
    }
}


