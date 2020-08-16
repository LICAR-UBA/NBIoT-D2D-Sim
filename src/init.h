#ifndef INIT_H_
#define INIT_H_

#include "tools.h"
#include "topology.h"
#include "pdr_dsr.h"
#include "edr_eed.h"
#include "pcg_basic.h"

/*--- Structure to store experimental parameters 
      the expected values are in this order: edr, eed, edr_mu, eed_mu,
      edr_s, eed_s, edr_e, eed_e ---------------------------------------------*/
struct input_output
{
    int tp_dc;
    float alpha;
    int tau;
    unsigned long int no_ues_bs;
    unsigned long int no_ues_nc;
    double * expected_edr;
    double * expected_eed;
    double * power;
    double * duty_cycle;
};

extern struct input_output * * thread_in_out;

void * calc_e2edr_e2ed(void * _thread_index);

extern pthread_mutex_t mutex_progress;

extern pthread_mutex_t mutex_cpu;

extern float progress;

extern int n_threads;

extern int comb_param;

extern int id_CORE;

extern unsigned int num_threads;

extern int num_taus;

extern int num_alpha;

void input(int thread_index);

void output(void);

#endif
