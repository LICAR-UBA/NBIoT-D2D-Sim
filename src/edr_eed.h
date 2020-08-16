#ifndef EDR_EED_H_
#define EDR_EED_H_

#include "tools.h"
#include "topology.h"

/*--- Struct EDR,EED -------------------------------------------------------- */
struct edr_eed
{
    double edr;
    double eed;
};

/*--- Calculation of the EDR ------------------------------------------------ */
double calc_edr( int * p_dws, double * p_pdr_due_rec,
                 double * p_pdr_rec_bs,  int no_relays, int tau );

/*--- Calc. Optimal EDR ------------------------------------------------------*/
struct edr_eed calc_optimal_edr( double * p_pdr_due_rec, double * p_pdr_rec_bs,
                                 int * p_dsr_due, struct topology * t, int tau,
                                 int * p_dws_due, int * p_dws_due_opt );

/*--- Calculation of the EED ------------------------------------------------ */
double calc_eed( int * p_dws, double * p_pdr_due_rec,
               double * p_pdr_rec_bs,  int no_relays, int _nn0, int c, int tau);

#endif

