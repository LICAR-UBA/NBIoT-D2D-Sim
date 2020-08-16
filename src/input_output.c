#include "init.h"

void input(int thread_index)
{

    /*--- Initializating values and memory spaces of the simulation ----------*/

    unsigned long int no_ues_bs = _no_ues_bs;

    unsigned long int no_ues_nc = _no_ues_nc;

    int taus[] = _nn;

    double alpha[] = _alpha;

    int num_taus = sizeof(taus)/sizeof(taus[0]);

    int num_alpha = sizeof(alpha)/sizeof(alpha[0]);

    /* No. of parameters combinations depend of num of taus, num of alpha,
       and multiplying by two: once for tp scenario, once for dc scenario.
       Multiplied by 2 because we are using both: tp and duty cicles scenarios*/

    comb_param = num_taus * num_alpha * 2;

    thread_in_out[thread_index] = calloc ( comb_param, sizeof( struct input_output ) );

    int pos = 0;

    for(int k = 0; k < 2; k++)
    {
        for (int m = 0; m < num_alpha; m++)
        {
            for (int l = 0; l < num_taus; l++)
            {
                /*--- Set simulation input parameters ------------*/
                if( k == 0)
                {
                    thread_in_out[thread_index][pos].expected_edr 
                    = calloc (w_load[thread_index].quota*_no_duty_cycle,
                                                        sizeof( double ) );
                    thread_in_out[thread_index][pos].expected_eed 
                    = calloc (w_load[thread_index].quota*_no_duty_cycle,
                                                        sizeof( double ) );
                    thread_in_out[thread_index][pos].power 
                    = (double *) malloc ( sizeof( double ) );
                    thread_in_out[thread_index][pos].duty_cycle 
                    = calloc ( _no_duty_cycle, sizeof( double ) );
                    thread_in_out[thread_index][pos].power[0] = _effective_power;
                    for (int i = 0; i < _no_duty_cycle; i++)
                    {
                        thread_in_out[thread_index][pos].duty_cycle[i] 
                                                      = _dc_min + i * _delta_dc;
                    }
                }
                else
                {
                    thread_in_out[thread_index][pos].expected_edr
                    = calloc (w_load[thread_index].quota*_no_trans_power,
                                                        sizeof( double ) );
                    thread_in_out[thread_index][pos].expected_eed
                    = calloc (w_load[thread_index].quota*_no_trans_power,
                                                        sizeof( double ) );
                    thread_in_out[thread_index][pos].power 
                    = calloc ( _no_trans_power, sizeof( double ) );
                    thread_in_out[thread_index][pos].duty_cycle 
                    = (double *) malloc ( sizeof( double ) );
                    thread_in_out[thread_index][pos].duty_cycle[0] = _effective_dc;
                    for (int i = 0; i < _no_trans_power; i++)
                    {
                        thread_in_out[thread_index][pos].power[i]
                        = _p_ue_min + i * _delta_p;
                    }
                }
                thread_in_out[thread_index][pos].tp_dc = k;
                thread_in_out[thread_index][pos].no_ues_bs = no_ues_bs;
                thread_in_out[thread_index][pos].no_ues_nc = no_ues_nc;
                thread_in_out[thread_index][pos].alpha = alpha[m];
                thread_in_out[thread_index][pos].tau = taus[l];
                pos++;
            }
         }
    }
}

/*--- Calculate and print to files final results ----------------*/
void output(void)
{
    FILE * fp1;
    FILE * fp2;
    char filename1[25] = "tp_expected_values.csv";
    char filename2[25] = "dc_expected_values.csv";
    fp1 = fopen (filename1,"w");
    fp2 = fopen (filename2,"w");
    fprintf( fp1, "power_trans,edr,dev_stand_edr,eed,dev_stand_eed,alpha,tau\n");
    fprintf( fp2, "duty_cycle,edr,dev_stand_edr,eed,dev_stand_eed,alpha,tau\n");

    int pos;

    double sum_tp_edr[_no_trans_power];
    double sum_tp_eed[_no_trans_power];
    double sqr_dif_tp_edr[_no_trans_power];
    double sqr_dif_tp_eed[_no_trans_power];
    double mean_tp_edr[_no_trans_power];
    double std_dev_tp_edr[_no_trans_power];
    double mean_tp_eed[_no_trans_power];
    double std_dev_tp_eed[_no_trans_power];

    int no_duty_cycle = _no_duty_cycle;
    double sum_dc_edr[no_duty_cycle];
    double sum_dc_eed[no_duty_cycle];
    double sqr_dif_dc_edr[no_duty_cycle];
    double sqr_dif_dc_eed[no_duty_cycle];
    double mean_dc_edr[no_duty_cycle];
    double std_dev_dc_edr[no_duty_cycle];
    double mean_dc_eed[no_duty_cycle];
    double std_dev_dc_eed[no_duty_cycle];

    for (int i = 0; i < comb_param; i++)
    {
        for (int l = 0; l < _no_trans_power; l++)
        {
           sum_tp_edr[l] = 0;
           sum_tp_eed[l] = 0;
           sqr_dif_tp_edr[l] = 0;
           sqr_dif_tp_eed[l] = 0;
           mean_tp_edr[l] = 0;
           std_dev_tp_edr[l] = 0;
           mean_tp_eed[l] = 0;
           std_dev_tp_eed[l] = 0;
        }

       for (int l = 0; l < _no_duty_cycle; l++)
       {
           sum_dc_edr[l] = 0;
           sum_dc_eed[l] = 0;
           sqr_dif_dc_edr[l] = 0;
           sqr_dif_dc_eed[l] = 0;
           mean_dc_edr[l] = 0;
           std_dev_dc_edr[l] = 0;
           mean_dc_eed[l] = 0;
           std_dev_dc_eed[l] = 0;
        }
        for (int j = 0; j < n_threads; j++ )
        {
            pos = 0;
            for( int k = 0; k < w_load[j].quota; k++ )
            {
                if (thread_in_out[j][i].tp_dc)
                {
                    for( int m = 0; m < _no_trans_power; m++ )
                    {
                        sum_tp_edr[m] += thread_in_out[j][i].expected_edr[pos];
                        sum_tp_eed[m] += thread_in_out[j][i].expected_eed[pos];
                        pos++;
                    }
                }else
                {
                    for( int m = 0; m < _no_duty_cycle; m++ )
                    {
                        sum_dc_edr[m] += thread_in_out[j][i].expected_edr[pos];
                        sum_dc_eed[m] += thread_in_out[j][i].expected_eed[pos];
                        pos++;
                    }
                }
            }
        }
        if (thread_in_out[0][i].tp_dc)
        {
                for( int m = 0; m < _no_trans_power; m++ )
                {
                    mean_tp_edr[m] = sum_tp_edr[m] / _no_topo;
                    mean_tp_eed[m] = sum_tp_eed[m] / _no_topo;
                }
        }else
        {
                for( int m = 0; m < _no_duty_cycle; m++ )
                {
                    mean_dc_edr[m] = sum_dc_edr[m] / _no_topo;
                    mean_dc_eed[m] = sum_dc_eed[m] / _no_topo;
                }
        }
        for (int j = 0; j < n_threads; j++ )
        {
            pos = 0;
            for( int k = 0; k < w_load[j].quota; k++ )
            {
                if (thread_in_out[j][i].tp_dc)
                {
                    for( int m = 0; m < _no_trans_power; m++ )
                    {
                        sqr_dif_tp_edr[m] += pow(mean_tp_edr[m] 
                                  - thread_in_out[j][i].expected_edr[pos], 2);
                        sqr_dif_tp_eed[m] += pow(mean_tp_eed[m] 
                                  - thread_in_out[j][i].expected_eed[pos], 2);
                        pos++;
                    }
                }else
                {
                    for( int m = 0; m < _no_duty_cycle; m++ )
                    {
                        sqr_dif_dc_edr[m] += pow(mean_dc_edr[m] 
                                  - thread_in_out[j][i].expected_edr[pos], 2);
                        sqr_dif_dc_eed[m] += pow(mean_dc_eed[m] 
                                  - thread_in_out[j][i].expected_eed[pos], 2);
                        pos++;
                    }
                }
            }
        }
        if (thread_in_out[0][i].tp_dc)
        {
            for( int m = 0; m < _no_trans_power; m++ )
            {
                std_dev_tp_edr[m] = sqrt(sqr_dif_tp_edr[m] / (_no_topo-1));
                std_dev_tp_eed[m] = sqrt(sqr_dif_tp_eed[m] / (_no_topo-1));
                fprintf( fp1, "%.0lf,%.4lf,%.4lf,%.4lf,%.4lf,%.2f,%d\n", 
                          thread_in_out[0][i].power[m], mean_tp_edr[m], 
                          std_dev_tp_edr[m], mean_tp_eed[m], std_dev_tp_eed[m],
                          thread_in_out[0][i].alpha, thread_in_out[0][i].tau );
            }
        }else
        {
            for( int m = 0; m < _no_duty_cycle; m++ )
            {
                std_dev_dc_edr[m] = sqrt(sqr_dif_dc_edr[m] / (_no_topo-1));
                std_dev_dc_eed[m] = sqrt(sqr_dif_dc_eed[m] / (_no_topo-1));
                fprintf( fp2, "%.2lf,%.4lf,%.4lf,%.4lf,%.4lf,%.2f,%d\n", 
                          thread_in_out[0][i].duty_cycle[m], mean_dc_edr[m], 
                          std_dev_dc_edr[m], mean_dc_eed[m], std_dev_dc_eed[m],
                          thread_in_out[0][i].alpha, thread_in_out[0][i].tau );
            }
        }

    }

/*--- Close files ----------------------------------------------------*/
    fclose( fp1 );
    fclose( fp2 );
}
