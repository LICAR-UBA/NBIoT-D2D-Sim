/*--- Main parameters --------------------------------------------------------*/

#ifndef PARAMETERS_H_
#define PARAMETERS_H_

/*--- No. of Threads ---*/
#define _no_threads 3

/*--- No. of CPU's cores ---*/
#define _CPU_CORES 3

/*--- No. of packets (W in the paper) ---*/
#define _no_packets 50

/*--- No. of topologies (experiments) ---*/
#define _no_topo 30

/*--- Duty cycle ---*/
#define _dc_max 0.50
#define _dc_min 0.10
#define _delta_dc 0.10
#define _no_duty_cycle ( ( _dc_max - _dc_min ) / _delta_dc + 1 )
#define _effective_dc 0.20

/*--- Power from DUE and non-coverage UEs to Relays ---*/
#define _p_ue_max 23 /*--- dBm -*/
#define _p_ue_min 8 /*--- dBm -*/
#define _no_trans_power 4
#define _delta_p ( ( _p_ue_max - _p_ue_min ) / ( _no_trans_power - 1 ) )
#define _effective_power 13 /*--- dBm -*/

/*--- No. repetitions and codification factor ---*/
#define _nrep 1
#define _sinr_cod 0 /*--- dBm --*/

/*--- Noise power --*/
#define _sigma2 -88.5 /*--- dBm --*/
#define _sigma2_W 1.412e-12

/*--- Packet size (L in the paper) ---*/
#define _packet_size 336

/*--- Transfer block size (l in the paper) -*/
#define _tbs 168

/*--- L/l: No blocks per packet -------*/
#define _no_tb ( _packet_size / _tbs )

/*--- Maximum no. of retransmitions ---*/
#define _nn { 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40 }

/*--- Path-loss exponent ---*/
#define _alpha { 2.0, 2.1, 2.2, 2.3, 2.4, 2.5 }

/*--- Mu from the Rayleigh channel ---*/
#define _mu 1
#define _lambda ( 1 / _mu )

/*--- Base station position, radius and power ---*/
#define _no_bs 1
#define _bs_x { 5500 } /*--- meters --*/
#define _bs_y { 7500 } /*--- meters --*/
#define _bs_r { 5000 } /*--- meters --*/
#define _bs_p { 23 } /*--- dBm --*/

/*--- DUE positions, radius and power ----*/
/*--- Just one DUE is allowed ----*/
#define _no_dues 1
#define _due_x 10550  /*--- meters ----*/
#define _due_y 7500  /*--- meters ----*/
#define _due_r 150  /*--- meters ----*/

/*--- No. of UEs into the BS footprint and non-coverge -----------------------*/

/*--- No. of devices into the BS footprint (area_by_lambda) ---*/
#define _no_ues_bs 20421

/*--- No. of devices into the non-coverage area (area_by_lambda) ---*/
#define _no_ues_nc 300
#define _effective_nc_interference 1.0
/* Densities nc: 
Urban scenario:
                 600 ues/km2 => 524 ues, 500 ues/km2 => 437 ues,
                 350 ues/km2 => 306 ues, 250 ues/km2 => 218 ues,
                 150 ues/km2 => 131 ues.
Suburban scenario:
                 3.5 ues/km2 => 512 ues, 2.5 ues/km2 => 366 ues,
                 2.0 ues/km2 => 293 ues, 1.5 ues/km2 => 219 ues,
                 1.0 ues/km2 => 146 ues. */

/*--- XY max and min into a Topology scenario --------------------------------*/
/*--- TODO Validate dues plus bs axis and their radius are into these values -*/
#define _x_max 15000
#define _y_max 15000
#define _x_min 0
#define _y_min 0

/*--- Inter-cell Interference ----*/
#define _intercell_interference 0

/*--- Pi ---*/
#define _pi 3.14159265358979323846

#endif

