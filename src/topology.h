#ifndef TOPOLOGY_H_
#define TOPOLOGY_H_

#include "tools.h"

/*--- Topology structures ----------------------------------------------------*/

struct nc_ues_axis
{
    double nc_ue_x[_no_ues_nc];
    double nc_ue_y[_no_ues_nc];
    double active[_no_ues_nc];
    int channel[_no_ues_nc];
};

struct bs_ues_axis
{
    double bs_ue_x[_no_ues_bs];
    double bs_ue_y[_no_ues_bs];
};

struct bs_topology
{
    double bs_x;
    double bs_y;
    double fp;
    int no_bs_relays;
    unsigned long int no_bs_ues;
    double d2d_power;
    double nbiot_power;
    struct bs_ues_axis * bs_ues_x_y;
};

struct topology
{
    int no_dues;
    double due_x;
    double due_y;
    double due_r;
    int total_no_relays;
    int no_bs;
    struct bs_topology * bs_topologies;
    unsigned long int no_nc_ues;
    struct nc_ues_axis * nc_ues_x_y;
    double x_min;
    double x_max;
    double y_min;
    double y_max;
    int intercell_interference;
};

/*--- Calculate topologies ---------------------------------------------------*/
void calc_nc_ue_pos(struct topology * t, int thread_index );

void calc_bs_topologies(double bs_x, double bs_y, double fp, double nbiot_power, 
                        unsigned long int no_ues_bs, struct topology * t, 
                        int position, int thread_index );

void calc_topology( struct topology *t, unsigned long int no_ues_bs, 
                               unsigned long int no_ues_nc, int thread_index );

/*--- Save topology ----------------------------------------------------------*/
void save_topology(char filename[], struct topology t);


#endif
