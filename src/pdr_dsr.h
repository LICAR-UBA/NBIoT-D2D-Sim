#ifndef PDR_DSR_H_
#define PDR_DSR_H_

#include "tools.h"
#include "topology.h"

/*--- SINR ------------------------------------------------------------------ */
double calc_sinr( double x0, double y0, struct topology * t, int l, int k,
                  double ue_power, double nc_ue_power, double active, 
                  float alpha, int thread_index, int channel,
                  double lambda, double sigma2, double sinr_cod, int mode );

/*--- Calc. PDR --------------------------------------------------------------*/
void calc_pdr( double * p_pdr, struct topology * t,
               double dc, double tp, int from_due, float alpha, int thread_index );

/*--- Calc. DSR --------------------------------------------------------------*/
void calc_dsr(int * p_dsr_u, int no_relays, double dc, int tau,
              int * p_dsr_due_aux, int * p_dsr_due_offset, 
              int * p_dsr_due_idx, int thread_index );

#endif
