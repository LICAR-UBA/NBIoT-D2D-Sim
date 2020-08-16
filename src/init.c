#define _GNU_SOURCE
#include "init.h"

unsigned long long int contador = 0;

pcg32_random_t * nums_random;

pthread_mutex_t mutex_progress = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t mutex_cpu = PTHREAD_MUTEX_INITIALIZER;

float progress = 0;

int n_threads = 0;

int comb_param = 0;

int id_CORE = 0;

unsigned int num_threads;

struct input_output * * thread_in_out;

struct workload * w_load;

int num_taus;

int num_alpha;

int main()
{

    n_threads = _no_threads;

     /*--- Initialization of random numbers per thread -----------------------*/

    nums_random = calloc (n_threads, sizeof( pcg32_random_t ));

    for (int i = 0; i < n_threads; i++)
    {
        pcg32_srandom_r(&nums_random[i], time(NULL), (intptr_t)&nums_random[i]);
    }

    int no_topologies = _no_topo;

    /*---Calculate the workload for each thread ------------------------------*/

    w_load = calloc ( n_threads, sizeof( struct workload ) );

    workload(w_load, n_threads, no_topologies);

    pthread_t thread_id[n_threads];

    int thread_indexes[n_threads];

    num_threads = _no_threads;

    thread_in_out = calloc ( n_threads, sizeof( struct input_output * ) );

    /*--- Initialize input parameters and data storage space for each thread -*/

    for (int i = 0; i < n_threads; i++ )
    {
        input(i);
    }

    /*--- Run simulation thread ----------------------------------------------*/
    for (int i = 0; i < n_threads; i++ )
    {
        thread_indexes[i] = i;
        pthread_create(&thread_id[i], NULL, calc_e2edr_e2ed,
                                        (void *)&thread_indexes[i]);
    }

    /*--- Wait for all threads -----------------------------------------------*/

    do {
        __sync_synchronize();
        usleep(0.0001);
    } while (num_threads);

    /*--- Calculate and save the simulation results to files -----------------*/

    output();

    for (int i = 0; i < n_threads; i++ )
    {
        for (int in_out_index = 0; in_out_index < comb_param; in_out_index++)
        {
            free( thread_in_out[i][in_out_index].expected_edr );
            free( thread_in_out[i][in_out_index].expected_eed );
            free( thread_in_out[i][in_out_index].power );
            free( thread_in_out[i][in_out_index].duty_cycle );
        }
    }
    free( thread_in_out );
    free( w_load );
    free( nums_random );

    printf("World peace was reached!\n");
    return 0;
}


