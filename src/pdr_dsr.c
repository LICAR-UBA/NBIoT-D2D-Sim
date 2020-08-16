#include "pdr_dsr.h"


/*--- SINR ------------------------------------------------------------------ */
    
double calc_sinr( double x, double y, struct topology * t, int l, int k,
                  double ue_power, double nc_ue_power, double active, 
                  float alpha, int thread_index, int channel, 
                  double lambda, double sigma2, double sinr_cod, int mode )
{
    double x0, x1, y0, y1;
    if (mode)
    {
        x1 = x;
        y1 = y;
        x0 = t->bs_topologies[l].bs_ues_x_y->bs_ue_x[k];
        y0 = t->bs_topologies[l].bs_ues_x_y->bs_ue_y[k];
    }else
    {
        x0 = x;
        y0 = y;
        x1 = t->bs_topologies[l].bs_ues_x_y->bs_ue_x[k];
        y1 = t->bs_topologies[l].bs_ues_x_y->bs_ue_y[k];
    }

    /*--- Channel gain ----------------------*/
    double h_a_b = expon(lambda, thread_index);

    /*--- Distance u-rec --------------------*/
    double l_a_b = distance( x0, x1, y0, y1 );

    /*--- Power of u measured in rec --------*/
    double a = h_a_b * pow( 10, ue_power / 10. ) / 1000. * pow( l_a_b, -alpha );

    /*--- Add interference from other bs ues ----*/
    double b = 0;
    double l_i_b = 0;
    double h_i_b = 0;

    if( t->intercell_interference )
    {
        for (int j = 0; j < t->no_bs; j++)
        {
            /*--- Exclude self BS --------*/
           if( j != l )
           {
                int no_bs_ues = t->bs_topologies[j].no_bs_ues;
                double nbiot_power = t->bs_topologies[j].nbiot_power;
                double * ue_x = t->bs_topologies[j].bs_ues_x_y->bs_ue_x;
                double * ue_y = t->bs_topologies[j].bs_ues_x_y->bs_ue_y;

                for (int i = 0; i < no_bs_ues; i++)
                {
                     /*--- Selecting active nodes and available channels -----*/
                    int channel_bs_ue = (int)rnd(1,50,thread_index);
                    if ( ( rnd(0,1, thread_index) < active ) 
                                      && ( channel == channel_bs_ue ) )
                    {
                        /*--- Distance u-rec ------------------------*/
                        if( ( x0 == t->due_x ) && ( y0 == t->due_y ) )
                            l_i_b = distance( ue_x[i], x1, ue_y[i], y1 );
                        else
                            l_i_b = distance( ue_x[i], x0, ue_y[i], y0 );

                        if( l_i_b > 0 )
                        {
                            h_i_b = expon(_lambda, thread_index );
                        //TODO: non-coverage needs more flexibility with this if
                            if( ( x0 == t->due_x ) && ( y0 == t->due_y ) )
                            {   
                                double d2d_power = pow( 10, nc_ue_power 
                                                        / 10. ) / 1000.; 
                                b += h_i_b * d2d_power * pow( l_i_b, -alpha );
                            }
                            else
                            {
                                b += h_i_b * nbiot_power * pow( l_i_b, -alpha );
                            }

                        }
                    }
                }
            }
        }
    }

    /*--- Add interference from non-coveraged ues --------*/
    for (unsigned long int j = 0; j < t->no_nc_ues; j++)
    {
        /*--- Selecting actives nodes, and available channels -*/
        if ( ( t->nc_ues_x_y->active[j] < _effective_nc_interference ) && 
                                      ( channel == t->nc_ues_x_y->channel[j] ) )
        {
            /*--- Distance ue-relay ------------------*/
            l_i_b = distance( t->nc_ues_x_y->nc_ue_x[j],
                     x1, t->nc_ues_x_y->nc_ue_y[j], y1 );

            if( l_i_b > 0 )
            {
                h_i_b = expon(lambda, thread_index);
                double d2d_power = pow( 10, nc_ue_power / 10. ) / 1000.;
                b += h_i_b * d2d_power * pow( l_i_b, -alpha );
            }
        }
    }

    /*--- Gaussian noise (dBm to W) ------*/
    b += pow( 10, sigma2 / 10. ) / 1000.;

    return  a / b + sinr_cod;
}

/*--- Calc. PDR --------------------------------------------------------------*/

void calc_pdr( double * p_pdr, struct topology * t,
               double dc, double tp, int from_due, float alpha, int thread_index )
{
    int m = 0;
    int no_packets = _no_packets;
    int no_tb = _no_tb;
    int tbs = _tbs;
    int nrep = _nrep;
    double lambda = _lambda;
    double sigma2 = _sigma2;
    double sinr_cod = _sinr_cod;
    for (int l = 0; l < t->no_bs; l++)
    {
        for (int k = 0; k < t->bs_topologies[l].no_bs_relays; k++)
        {
            p_pdr[m] = 0;
            for (int i = 0; i < no_packets; i++)
            {
                double mult = 1.;
                double bler = -1.;
                int channel = (int)rnd(1,50,thread_index);
                for (int j = 0; j < no_tb; j++)
                {
                    double sinr = 0;
                    if ( from_due )
                    {
                        sinr = calc_sinr( t->due_x, t->due_y, t, l, k, 
                                          tp, tp, dc, alpha, thread_index, 
                                          channel, lambda, sigma2, sinr_cod, 0 );
                    }
                    else
                    {
                        sinr = calc_sinr( t->bs_topologies[l].bs_x,
                                          t->bs_topologies[l].bs_y, t, l, k, 
                                          t->bs_topologies[l].nbiot_power,
                                          tp, dc, alpha, thread_index, 
                                          channel, lambda, sigma2, sinr_cod, 1 ); 
                    }

                    double p_b = 0.5 * erfc( sqrt( sinr / 2. ) );
                    
                    bler = pow( 1 - pow( 1 - p_b, tbs ), nrep );

                    mult *= ( 1 - bler );

                }
                p_pdr[m] += mult;
            }

            p_pdr[m] /= no_packets;
            m++;
        }
    }
}

/*--- Calc. DSR --------------------------------------------------------------*/

void calc_dsr(int * p_dsr_u, int no_relays, double dc, int tau, 
              int * p_dsr_due, int * p_dsr_due_offset, 
              int * p_dsr_due_idx, int thread_index )
{

    for (int k = 0; k < no_relays * (tau - 1); k++)
    {
        p_dsr_u[k] = 0;
    }
    for (int k = 0; k < no_relays; k++)
    {
        int counter = tau * dc;
        while( counter > 0 )
        {
            int idx = rnd(0, tau - 1, thread_index );
            if ( p_dsr_u[ idx + k * (tau - 1) ] != 1 )
            {
                p_dsr_u[ idx + k * (tau - 1) ] = 1;
                counter--;
            }
        }

        int offset = 0;
        while ( p_dsr_u[ offset + k * (tau - 1)  ] == 0 )
            offset++;

        p_dsr_due_offset[k] = offset;
        p_dsr_due_idx[k] = k;
    }

    quick_sort(p_dsr_due_offset, p_dsr_due_idx, 0, no_relays-1);

    /*--- Copy p_dsr_u to p_dsr_due according to p_dsr_due_idx indexes -------*/
    for (int k = 0; k < no_relays; k++)
    {
        /*--- Copy row p_dsr_due_idx[k] from p_dsr_u to row k from p_dsr_due -*/
        for (int n = 0; n < (tau - 1); n++)
            p_dsr_due[ n + k * (tau - 1) ] = p_dsr_u[ n + p_dsr_due_idx[k] 
                                                                  * (tau - 1) ];
    }
}



