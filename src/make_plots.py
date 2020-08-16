import os
import csv
import matplotlib.pyplot as plt
import numpy as np
import sys

###############################################################################
# get no_ues_bs and no_ues_nc
###############################################################################

def get_array(label, row):
    array = []
    if label in row:
        i = 0
        while( i < len(row) and row[i] != '{' ):
            i = i + 1
        i = i + 1
        i0 = i
        while( i < len(row) and row[i] != '}' ):
            i = i + 1
        i1 = i
        array = [ float(x) for x in (row[i0:i1].split(',')) ]
    return array

def get_params():

    # Get number of UEs at the BS from parameters.h
    params = {}
    with open('../src/parameters.h','r') as fp:
       row = fp.readline()
       while row:         

            aux = get_array('_no_ues_bs', row)
            if( len(aux) ): params['no_ues_bs'] = aux

            aux = get_array('_no_ues_nc', row)
            if( len(aux) ): params['no_ues_nc'] = aux

            aux = get_array('_bs_x', row)
            if( len(aux) ): params['bs_x'] = aux

            aux = get_array('_bs_y', row)
            if( len(aux) ): params['bs_y'] = aux

            aux = get_array('_bs_r', row)
            if( len(aux) ): params['bs_r'] = aux

            aux = get_array('_due_x', row)
            if( len(aux) ): params['due_x'] = aux

            aux = get_array('_due_y', row)
            if( len(aux) ): params['due_y'] = aux

            aux = get_array('_due_r', row)
            if( len(aux) ): params['due_r'] = aux

            row = fp.readline()

    return params


###############################################################################
# plot e2edr and e2ed
###############################################################################
def plot_e2edr_e2ed(params):

    no_ues_bs = params['no_ues_bs']
    no_ues_nc = params['no_ues_nc']

    y_axis_initials = params['y_axis_initials']
    y_axis_label1 = params['y_axis_label1']
    x_axis_initials = params['x_axis_initials']
    x_axis_label0 = params['x_axis_label0']
    x_axis_label1 = params['x_axis_label1']

    lstyle = ["-","--",":"]

    n = len(no_ues_bs)
    m = len(no_ues_nc)
    
    for i in range(n):
        ax = plt.gca()
        for j in range(m):

            mu = []
            s_1 = []
            s_0 = []
            e_1 = []
            e_0 = []
            x_axis = []

            a = int( no_ues_bs[i] )
            b = int( no_ues_bs[i] * no_ues_nc[j] )

            #filename = 'nuebs' + str(a) + '_nuenc' + str(b) + '_' + \
            #            y_axis_initials + '_' + x_axis_initials + '.csv'
            filename = 'all.csv'

            with open(filename) as csv_file:
                csv_reader = csv.DictReader(csv_file)
                line_count = 0
                for row in csv_reader:
                    x_axis.append( float(row[x_axis_label0]) )
                    mu.append( float(row['mu']) )
                    s_1.append( float(row['mu']) + float(row['s']) )
                    s_0.append( float(row['mu']) - float(row['s']) )
                    e_1.append( float(row['mu']) + float(row['e']) )
                    e_0.append( float(row['mu']) - float(row['e']) )
                    line_count += 1

            l = "No. BS-UEs:" + str(a) + ", No. NC-UEs:"+ str(b)
            plt.plot(x_axis, mu, color="gray", linestyle=lstyle[j], label=l)
            plt.fill_between(x_axis, s_0, s_1, alpha=.1)
            plt.fill_between(x_axis, e_0, e_1, color="red", alpha=.1)
            plt.scatter(x_axis, mu, color="gray", marker="s", s=30)


        plt.legend(loc='upper right')
        #plt.ylim(0.7, 1.1)
        ax.set(xlabel=x_axis_label1, ylabel=y_axis_label1)

        filename = 'nuebs' + str(int(no_ues_bs[i])) + '_' + y_axis_initials \
                   + '_' + x_axis_initials + '.png'
        plt.savefig(filename, dpi = 300)
        plt.clf()


###############################################################################
# plot maps
###############################################################################
def plot_maps(params):

    no_ues_bs = params['no_ues_bs']
    n = len(no_ues_bs)
    no_ues_nc = params['no_ues_nc']
    m = len(no_ues_nc)
    due_x = params['due_x']
    due_y = params['due_y']
    due_r = params['due_r']
    no_due = len(params['due_r'])
    bs_x = params['bs_x']
    bs_y = params['bs_y']
    bs_r = params['bs_r']
    no_bs = len(params['bs_r'])
    
    colors = ["red", "green", "green"]

    ax = plt.gca()
    
    for k in range(m):
        for j in range(n):

            a = int( no_ues_bs[j])
            b = int( no_ues_bs[j] * no_ues_nc[k] )

            for i in range(no_bs):

                bs_x = 0
                bs_y = 0
                bs_r = 0

                ue_x = []
                ue_y = []

                filename = 'topology_nuebs' + str(a) + \
                           '_nuenc' + str(b) + '_bs' + str(i) + '.csv'

                if os.path.isfile(filename):
                    with open(filename) as csv_file:
                        csv_reader = csv.DictReader(csv_file)
                        line_count = 0

                        row = next(csv_reader)
                        bs_x = float(row['x'])
                        bs_y = float(row['y'])
                        bs_r = float(row['r'])

                        for row in csv_reader:
                            ue_x.append( float(row['x']) )
                            ue_y.append( float(row['y']) )
                            line_count += 1

                        plt.scatter(ue_x, ue_y, color=colors[i], alpha=0.2, s=0.1)
                        plt.scatter([bs_x], [bs_y], color="purple", s=5.)
                        plt.annotate('Base station', (bs_x+100, bs_y+100) )
                        bs_circle = plt.Circle((bs_x, bs_y), bs_r, color=colors[i], alpha=0.2)
                        ax.add_artist(bs_circle)

            ue_x = []
            ue_y = []

            filename = 'topology_nuebs' + str(a) + \
                       '_nuenc' + str(b) + '_nc' + '.csv'
            if os.path.isfile(filename):
                with open(filename) as csv_file:
                    csv_reader = csv.DictReader(csv_file)
                    line_count = 0

                    row = next(csv_reader)
                    bs_x = float(row['x'])
                    bs_y = float(row['y'])

                    for row in csv_reader:
                        ue_x.append( float(row['x']) )
                        ue_y.append( float(row['y']) )
                        line_count += 1

                    plt.scatter(ue_x, ue_y, color="black", alpha=0.2, s=1.)

            plt.scatter(due_x, due_y, color="blue", s=5.)

            due_x_5 = [x + 100 for x in due_x] 
            due_y_5 = [y + 100 for y in due_y] 
            for i in range(len(due_x_5)):
                plt.annotate('DUE', (due_x_5[i], due_y_5[i]) )

            for i in range(len(due_x)):
                due_circle = plt.Circle((due_x[i], due_y[i]), due_r[i], color='blue', alpha=0.2)
                ax.add_artist(due_circle)

            #ax.set_xlabel('m')
            #ax.set_ylabel('m')

            ax.set(xlabel='m', ylabel='m')

            ax.set_ylim([-3000, 3000])
            ax.set_xlim([-1000, 17000])
            ax.set_aspect('equal')
            #ax.set_aspect('equal', 'datalim')
            filename = 'topology_nuebs' + str(a) + '_nuenc' + str(b) + '.png'
            plt.savefig(filename, dpi = 300)


###############################################################################
# Main
###############################################################################

# Get arguments

# no_ues_bs, no_ues_nc
params = get_params()

#params['x_axis_initials'] = 'tp'
#params['x_axis_label0'] = 'transmission_power'
#params['x_axis_label1'] = 'Transmission power \ dBm'
#params['y_axis_initials'] = 'e2edr'
#params['y_axis_label1'] = 'End to end delivery ratio'
#plot_e2edr_e2ed(params)
#params['y_axis_initials'] = 'e2ed'
#params['y_axis_label1'] = 'End to end delay'
#plot_e2edr_e2ed(params)

params['x_axis_initials'] = 'dc'
params['x_axis_label0'] = 'duty_cycle'
params['x_axis_label1'] = 'Duty cycle \ s'
params['y_axis_initials'] = 'e2edr'
params['y_axis_label1'] = 'End to end delivery ratio'
plot_e2edr_e2ed(params)
params['y_axis_initials'] = 'e2ed'
params['y_axis_label1'] = 'End to end delay'
plot_e2edr_e2ed(params)

# plot maps
plot_maps(params)



