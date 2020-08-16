#include "topology.h"

void calc_nc_ue_pos(struct topology * t, int thread_index )
{
    /*--- Calculation of the non-coveraged ues positions -------------------- */
    unsigned long int i = 0;
    while(i < t->no_nc_ues)
    {
        t->nc_ues_x_y->nc_ue_x[i] = rnd(t->x_min,t->x_max, thread_index );
        t->nc_ues_x_y->nc_ue_y[i] = rnd(t->y_min,t->y_max, thread_index );

        /* Exclude ue if the it is into any bs footprint */

        double d[t->no_bs];
        for( int j = 0; j < t->no_bs; j++)
            d[j] = distance(t->nc_ues_x_y->nc_ue_x[i],t->bs_topologies[j].bs_x,
                            t->nc_ues_x_y->nc_ue_y[i],t->bs_topologies[j].bs_y);

        int j = 0;

        while( ( j < t->no_bs ) && ( d[j] > t->bs_topologies[j].fp ) ) j++;

        if( j == t->no_bs )
        {
            t->nc_ues_x_y->active[i] = rnd( 0, 1, thread_index );
            t->nc_ues_x_y->channel[i] = (int)rnd( 1, 50, thread_index );
            i++;
        }

    }

}


void calc_bs_topologies(double bs_x, double bs_y, double fp, double nbiot_power,
                        unsigned long int no_ues_bs, struct topology * t,
                        int position, int thread_index )
{

    /*--- Calculation of the map -------------------------------------------- */

    /* Positions of the u and rec (relays) */

    /* no_bs_relays index divide ue_x and ue_y into two groups: */
    /* relays and no-relays */
    /* no_bs_relays is the index of the first no-relay in ue_x, ue_y */

    t->bs_topologies[position].fp = fp;

    unsigned long int no_bs_relays = t->bs_topologies[position].no_bs_relays;

    unsigned long int i = 0;

    unsigned long int count_relays = 0;

    while(i < no_ues_bs && count_relays < no_bs_relays)
    {
        t->bs_topologies[position].bs_ues_x_y->bs_ue_x[i] = 
                                            rnd(bs_x-fp,bs_x+fp, thread_index );
        t->bs_topologies[position].bs_ues_x_y->bs_ue_y[i] = 
                                            rnd(bs_y-fp,bs_y+fp, thread_index );

        /* If the ue is in the intersection of the bs footprint */
        double d0 = distance(bs_x, 
                             t->bs_topologies[position].bs_ues_x_y->bs_ue_x[i], 
                             bs_y, 
                             t->bs_topologies[position].bs_ues_x_y->bs_ue_y[i]);
        if ( d0 < fp )
        {
            /* If the ue is in the intersection of the bs and the due */
            double d1 = distance(t->due_x,
                             t->bs_topologies[position].bs_ues_x_y->bs_ue_x[i], 
                             t->due_y,
                             t->bs_topologies[position].bs_ues_x_y->bs_ue_y[i]);
            if ( d1 < t->due_r ) 
            {
                /* Swap the positions to relocate the relays at the begining */
                if ( i > count_relays )
                {
                    double x_aux = 
                              t->bs_topologies[position].bs_ues_x_y->bs_ue_x[i];
                    double y_aux = 
                              t->bs_topologies[position].bs_ues_x_y->bs_ue_y[i];
                    t->bs_topologies[position].bs_ues_x_y->bs_ue_x[i] =
                    t->bs_topologies[position].bs_ues_x_y->bs_ue_x[count_relays];
                    t->bs_topologies[position].bs_ues_x_y->bs_ue_y[i] =
                    t->bs_topologies[position].bs_ues_x_y->bs_ue_y[count_relays];
                    t->bs_topologies[position].bs_ues_x_y->bs_ue_x[count_relays] =
                                                                          x_aux;
                    t->bs_topologies[position].bs_ues_x_y->bs_ue_y[count_relays] =
                                                                          y_aux;
                }
                count_relays++;
            }
            i++;
        }
    }

    if (count_relays < no_bs_relays )
        t->bs_topologies[position].no_bs_relays = count_relays;

    t->bs_topologies[position].d2d_power = _effective_power;

    t->bs_topologies[position].nbiot_power = nbiot_power;

}

/*--- Calc. topology -------------------------------------------------------- */
void calc_topology( struct topology * t,
                    unsigned long int no_ues_bs, 
                    unsigned long int no_ues_nc, int thread_index )
{

    /* Set dues positions */
    t->no_dues = _no_dues;
    t->due_x = _due_x;
    t->due_y = _due_y;
    t->due_r = _due_r;

    /* Set BS positions */
    t->no_bs = _no_bs;
    double bs_x[] = _bs_x;
    double bs_y[] = _bs_y;
    double bs_r[] = _bs_r;
    double bs_p[] = _bs_p;

    t->x_min = _x_min;
    t->x_max = _x_max;
    t->y_min = _y_min;
    t->y_max = _y_max;

    for (int i = 0; i < _no_bs; i++){
        calc_bs_topologies(bs_x[i], bs_y[i], bs_r[i], bs_p[i], no_ues_bs, t, i,
                                                                 thread_index );
    }

    /* Calc. non-covereged ue positions */

    t->no_nc_ues = no_ues_nc;

    calc_nc_ue_pos(t, thread_index);

    t->intercell_interference = _intercell_interference;

}

/*--- Save topology ----------------------------------------------------------*/

void save_topology(char filename[], struct topology t)
{
    for( int l = 0; l < t.no_bs; l++)
    {
        char filename0[50];
        snprintf(filename0, 50, "%s_bs%d.csv", filename, l);

        FILE * fp;
        fp = fopen (filename0,"w");
        fprintf( fp, "x,y,r\n" );
        fprintf( fp, "%lf,%lf,%lf\n", t.bs_topologies[l].bs_x,
                                      t.bs_topologies[l].bs_y,
                                      t.bs_topologies[l].fp );  
        for( unsigned long int k = 0; k < t.bs_topologies[l].no_bs_ues; k++)
        {
           fprintf( fp, "%lf,%lf\n", t.bs_topologies[l].bs_ues_x_y->bs_ue_x[k],
                                     t.bs_topologies[l].bs_ues_x_y->bs_ue_y[k] );
        }

        fclose (fp);
    }

    if( t.no_nc_ues > 0 )
    {
        char filename0[50];
        strcpy(filename0, filename);
        strcat(filename0, "_nc.csv");
        FILE * fp;
        fp = fopen (filename0,"w");
        fprintf( fp, "x,y\n" );  
        for( unsigned long int k = 0; k < t.no_nc_ues; k++)
        {
           fprintf( fp, "%lf,%lf\n", t.nc_ues_x_y->nc_ue_x[k],
                                     t.nc_ues_x_y->nc_ue_y[k] );
        }
        fclose (fp);
    }
}
