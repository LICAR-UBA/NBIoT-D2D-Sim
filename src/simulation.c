#define _GNU_SOURCE
#include "init.h"


void * calc_e2edr_e2ed(void * _thread_index)
{

/*--- CPU's Cores asigment ---------------------------------------------------*/

    pthread_mutex_lock(&mutex_cpu);

        /*--- Sets the CPU affinity mask of the thread thread to the CPU set  
        pointed to by cpuset */
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(id_CORE, &cpuset);
        int s;
        s = pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
        if (s != 0)
            perror("Cpu's core assignment to thread failed.");
        s = pthread_getaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
        if (s != 0)
           perror("Getting CPU's core affinity thread failed.");
        id_CORE++;
        if (id_CORE > _CPU_CORES-1)
            id_CORE = 0;

    pthread_mutex_unlock(&mutex_cpu);

    int thread_index = * (int *) _thread_index;

    /*--- Memory spaces for topologies ---------------------------------------*/

    struct input_output * p_in_out;

    int no_bs = _no_bs;

    int c_p = comb_param;

    int n1 = _no_trans_power;

    int n2 = _no_duty_cycle;

    int no_topo = _no_topo;

    p_in_out = thread_in_out[thread_index];

    struct nc_ues_axis * nc_x_y;
    nc_x_y = (struct nc_ues_axis *) malloc(sizeof(struct nc_ues_axis));

    struct bs_ues_axis * bs_ues_x_y;
    bs_ues_x_y = (struct bs_ues_axis *) calloc(no_bs,sizeof(struct bs_ues_axis));

    struct bs_topology * bs_topologies = calloc(no_bs, 
                                                sizeof(struct bs_topology));

    /* El numero de relays es la densidad de ues de la bs por el area de  */
    /* interseccion de las dos circunferencias dibujadas por la due y la bs */

    int * no_relays_by_bs_due = (int *) calloc(no_bs,sizeof(int));

    calc_no_relays(no_relays_by_bs_due);

    int total_no_relays = 0;

    /* Create empty topology */
    struct topology t;

    t.bs_topologies = bs_topologies;

    t.nc_ues_x_y = nc_x_y;

    for ( int i = 0; i < no_bs; i++ )
    {
        total_no_relays += no_relays_by_bs_due[i];
        t.bs_topologies[i].bs_ues_x_y = bs_ues_x_y + i * sizeof(struct bs_ues_axis);
        t.bs_topologies[i].no_bs_relays = no_relays_by_bs_due[i];
        t.bs_topologies[i].d2d_power = _effective_power;
    }

    t.total_no_relays = total_no_relays;

    double * p_pdr_due_rec = calloc( total_no_relays, sizeof( double ) );

    double * p_pdr_rec_bs = calloc( total_no_relays, sizeof( double ) );

    int * p_dsr_due_offset = calloc( total_no_relays, sizeof( int ) );

    int * p_dsr_due_idx = calloc( total_no_relays, sizeof( int ) );

    int n;

    double tp, dc;

    int no_topologies = w_load[thread_index].quota;

    int * p_dsr_due[c_p];

    int * p_dsr_due_aux[c_p];

    int * p_dws_due[c_p];

    int * p_dws_due_opt[c_p];

    for (int in_out_index = 0; in_out_index < c_p; in_out_index++)
    {
        p_dsr_due[in_out_index] = calloc( total_no_relays 
                                         * ( p_in_out[in_out_index].tau - 1 ),
                                                           sizeof( int ) );

        p_dsr_due_aux[in_out_index] = calloc( total_no_relays 
                                             * ( p_in_out[in_out_index].tau - 1 ),
                                                               sizeof( int ) );

        p_dws_due[in_out_index] = calloc( total_no_relays 
                                         * ( p_in_out[in_out_index].tau - 1 ),
                                                           sizeof( int ) );

        p_dws_due_opt[in_out_index] = calloc( total_no_relays 
                                             * ( p_in_out[in_out_index].tau - 1 ),
                                                               sizeof( int ) );
    }

    /*--- Iterate through asigned topologies -----------------------------*/

    for(int j = 0; j < no_topologies; j++)
    {
        /*--- Create each topogy for each iteration ---------------*/
        calc_topology( &t, _no_ues_bs, _no_ues_nc, thread_index );

        for (int in_out_index = 0; in_out_index < c_p; in_out_index++)
        {
            /*--- if tp_dc == 1, is transmission power else is duty cycle ----*/
            if( p_in_out[in_out_index].tp_dc )
                n = n1;
            else
                n = n2;

            /*--- Iterate through trans. powers or duty cycles -----------*/
            for( int i = 0; i < n; i++ )
            {
                if(p_in_out[in_out_index].tp_dc)
                {
                    tp = p_in_out[in_out_index].power[i];
                    dc = p_in_out[in_out_index].duty_cycle[0];
                }else
                {
                    tp = p_in_out[in_out_index].power[0];
                    dc = p_in_out[in_out_index].duty_cycle[i];
                }
                /*--- Calculation of the PDR, DUE -> RELAY ---------------*/
                int from_due = 1;
                calc_pdr(p_pdr_due_rec, &t, dc, tp, from_due,
                                   p_in_out[in_out_index].alpha, thread_index );

                /*--- Calculation of the PDR, RELAY -> BS ----------------*/
                from_due = 0;
                calc_pdr(p_pdr_rec_bs, &t, dc, tp, from_due,
                                   p_in_out[in_out_index].alpha, thread_index );

                /*--- Calculation of DSR matrices for u ------------------*/
                calc_dsr(p_dsr_due_aux[in_out_index], t.total_no_relays, dc,
                         p_in_out[in_out_index].tau, p_dsr_due[in_out_index],
                         p_dsr_due_offset, p_dsr_due_idx, thread_index );

                /*--- Calculation of Optimal EDR -------------------------*/
                struct edr_eed e1 = calc_optimal_edr( p_pdr_due_rec, 
                                          p_pdr_rec_bs, p_dsr_due[in_out_index], 
                                          &t, p_in_out[in_out_index].tau, 
                                          p_dws_due[in_out_index], 
                                          p_dws_due_opt[in_out_index] );

                p_in_out[in_out_index].expected_edr[(j*n)+i] = e1.edr;
                p_in_out[in_out_index].expected_eed[(j*n)+i] = e1.eed;
            }
           /*--- Increase progress percentage and total spent time -----------*/
           pthread_mutex_lock(&mutex_progress);
               progress+=100/(float)(no_topo*c_p);
               printf("Progress: %.2f %% \n", progress);
           pthread_mutex_unlock(&mutex_progress);
        }
    }

    /*--- Frees  ------------------------------------------------------*/
    for (int in_out_index = 0; in_out_index < comb_param; in_out_index++)
    {
       free( p_dsr_due[in_out_index] );
       free( p_dsr_due_aux[in_out_index] );
       free( p_dws_due[in_out_index] );
       free( p_dws_due_opt[in_out_index] );
    }

    free( p_pdr_due_rec );
    free( p_pdr_rec_bs );
    free( p_dsr_due_offset );
    free( p_dsr_due_idx );
    free( bs_topologies );
    free( nc_x_y );
    free( bs_ues_x_y );

    __sync_fetch_and_sub(&num_threads,1);

    return NULL;
}
