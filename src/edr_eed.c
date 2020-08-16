#include "edr_eed.h"

/*--- Calculation of the EDR ------------------------------------------------ */

double calc_edr( int * p_dws, double * p_pdr_due_rec,
                 double * p_pdr_rec_bs, int no_relays, int tau )
{
    double s = 0;
    for (int n = 0; n < tau - 1; n++)
    {
        for (int k = 0; k < no_relays; k++)
        {
            /*--- Calc. of Q ----------*/
            double q = 1.;
            for (int j = 0; j < n; j++)
            {
                double s2 = 0;
                for (int m = 0; m < no_relays; m++)
                {
                    s2 += p_pdr_due_rec[m] * p_dws[ j + m * (tau - 1) ];
                }
                q *= ( 1 - s2 ) ;
            }
            q *= p_pdr_due_rec[k] * p_dws[ n + k * (tau - 1) ];

            /*--- Calc. of PDR (relay to bs) ---------------------*/
            double pdr = 1 - pow(1 - p_pdr_rec_bs[k], tau - 1 - n );

            /*--- Add to summatory -------------------------------*/
            s += q * pdr;
        }
    }
    return s;
}

/*--- Calc. Optimal EDR ------------------------------------------------------*/

struct edr_eed calc_optimal_edr( double * p_pdr_due_rec, double * p_pdr_rec_bs,
                                 int * p_dsr_due, struct topology * t, int tau,
                                 int * p_dws_due, int * p_dws_due_opt )
{
    /*--- Calculation of optimal DWS matrix for due --------------------------*/
    /*--- See algorithm 1 from "Narrowband Internet of Things Systems With
          Opportunistic D2D Communication" -----------------------------------*/

    for (int i = 0; i < t->total_no_relays * (tau - 1); i++)
    {
        p_dws_due[i] = 0;
        p_dws_due_opt[i] = 0;
    }

    double edr_opt = 0;
    for (int n = tau - 2; n >= 0; n--)
    {
        double pdr_2hop_max = -1;
        int k_max = -1;
        for (int k = 0; k < t->total_no_relays; k++)
        {
            if ( p_dsr_due[ n + k * (tau - 1) ] == 1 )
            {
                double pdr_2hop_due_k_bsk = p_pdr_due_rec[k] * p_pdr_rec_bs[k];
                if ( pdr_2hop_due_k_bsk > pdr_2hop_max )
                {
                    pdr_2hop_max = pdr_2hop_due_k_bsk;
                    k_max = k;
                }
            }
        }

        if ( k_max > -1 )
        {
            p_dws_due[ n + k_max * (tau - 1) ] = 1;
            double edr = calc_edr(p_dws_due, p_pdr_due_rec, 
                                  p_pdr_rec_bs, t->total_no_relays, tau );
            if ( edr >= edr_opt )
            {
                edr_opt = edr;
                p_dws_due_opt[ n + k_max * (tau - 1) ] = 1;
            }
            else
            {
                p_dws_due[ n + k_max * (tau - 1) ] = p_dws_due[ n + k_max * 
                                                                   (tau - 1) ];
            }
        }
    }

    struct edr_eed e;
    e.edr = edr_opt;
    e.eed = calc_eed(p_dws_due_opt, p_pdr_due_rec, p_pdr_rec_bs,
                                                 t->total_no_relays, 0, 1, tau);
    return e;
}


/*--- Calculation of the EED ------------------------------------------------ */

// TODO: Is tau0 parameter right?
double calc_eed( int * p_dws, double * p_pdr_due_rec,
                 double * p_pdr_rec_bs,  int no_relays, int tau0, int c, int tau)
{
    double s = 0;
    for (int n = 0; n < (tau - 1) * c + (tau - tau0) * (1 - c); n++)
    {
        for (int k = 0; k < no_relays; k++)
        {
            /*--- Calc. of Q --------------------*/
            double q = 1.;
            for (int j = 0; j < n; j++)
            {
                double s2 = 0;
                for (int m = 0; m < no_relays; m++)
                {
                    s2 += p_pdr_due_rec[m] * p_dws[ j + m * (tau - 1) ];
                }
                q *= ( 1 - s2 ) ;
            }
            q *= p_pdr_due_rec[k] * p_dws[ n + k * (tau - 1) ];  

            /*--- Calc. of PDR (relay to bs) ----------*/
            double pdr = 1 - pow(1 - p_pdr_rec_bs[k], 
                                (tau - 1 - n) * c + tau0 * (1 - c) );

            /*--- Calc. ED ----------------------------*/
            double ed = 0;
            for( int n2 = 0; n2 < (tau - 1 - n) * c + tau0 * (1 - c); n2++ )
            {
                ed += (n2 + 1) * pow( 1. - p_pdr_rec_bs[k], n2 ) 
                                                            * p_pdr_rec_bs[k];
            }
            if (pdr) ed /= pdr;

            /*--- Add to summatory --------------------*/
            s += q * pdr * ( n + 1 + ed );
        }
    }
    double edr = calc_edr( p_dws, p_pdr_due_rec, p_pdr_rec_bs, no_relays, tau );
    if( edr == 0 )
        return tau + 1;
    else
        return s / edr;
}
