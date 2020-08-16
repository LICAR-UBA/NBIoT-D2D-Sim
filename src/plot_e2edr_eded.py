import csv
import matplotlib.pyplot as plt
import numpy as np
import sys

# How to call the function:
#   python3 plot_e2edr_e2ed.py 'e2edr' 'tp'
#   python3 plot_e2edr_e2ed.py 'e2ed' 'tp'
#   python3 plot_e2edr_e2ed.py 'e2edr' 'dc'
#   python3 plot_e2edr_e2ed.py 'e2ed' 'dc' 

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
        array = [ int(x) for x in (row[i0:i1].split(',')) ]
    return array

def get_params():

    # Get number of UEs at the BS from parameters.h
    no_ues_bs = []
    no_ues_nc = []
    due_x = []
    due_y = []
    due_r = []
    params = {}
    with open('../src/parameters.h','r') as fp:
       row = fp.readline()
       while row:         
            params['no_ues_bs'] = get_array('_no_ues_bs', row)
            params['no_ues_nc'] = get_array('_no_ues_nc', row)
            params['bs_x'] = get_array('_bs_x', row)
            params['bs_y'] = get_array('_bs_y', row)
            params['bs_r'] = get_array('_bs_r', row)
            params['due_x'] = get_array('_due_x', row)
            params['due_y'] = get_array('_due_y', row)
            params['due_r'] = get_array('_due_r', row)
            row = fp.readline()

    return params


###############################################################################
# plot e2edr and e2ed
###############################################################################
def plot_e2edr_e2ed(params):

    no_ues_bs = params['no_ues_bs']
    no_ues_nc = params['no_ues_nc']

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
            transmission_power = []

            a = no_ues_bs[i]
            b = int( no_ues_bs[i] * no_ues_nc[j] )

            filename = 'nuebs' + str(a) + '_nuenc' + str(b) + '_' + y_axis_initials + '_' + x_axis_initials + '.csv'

            with open(filename) as csv_file:
                csv_reader = csv.DictReader(csv_file)
                line_count = 0
                for row in csv_reader:
                    transmission_power.append( float(row[x_axis_label0]) )
                    mu.append( float(row['mu']) )
                    s_1.append( float(row['mu']) + float(row['s']) )
                    s_0.append( float(row['mu']) - float(row['s']) )
                    e_1.append( float(row['mu']) + float(row['e']) )
                    e_0.append( float(row['mu']) - float(row['e']) )
                    line_count += 1

            l = "No. BS-UEs:" + str(a) + ", No. NC-UEs:"+ str(b)
            plt.plot(transmission_power, mu, color="gray", linestyle=lstyle[j], label=l)
            #plt.fill_between(transmission_power, s_0, s_1, alpha=.1)
            plt.fill_between(transmission_power, e_0, e_1, color="red", alpha=.1)
            plt.scatter(transmission_power, mu, color="gray", marker="s", s=30)


        plt.legend(loc='upper right')
        #plt.ylim(0.7, 1.1)
        ax.set(xlabel=x_axis_label1, ylabel=y_axis_label1)

        filename = 'nuebs' + str(no_ues_bs[i]) + '_' + y_axis_initials + '_' + x_axis_initials + '.png'
        plt.savefig(filename, dpi = 300)


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
    for i in range(no_bs):
        for j in range(n):
            for k in range(m):
                bs_x = 0
                bs_y = 0
                bs_r = 0

                ue_x = []
                ue_y = []

                filename = 'topology_nuebs' + str(no_ues_bs[j]) + \
                           '_nuenc' + str(no_ues_nc[k]) + '_bs' + str(i) + '.csv'

                if os.path.isfile(filename):
                    with open(filename) as csv_file:
                        csv_reader = csv.DictReader(csv_file)
                        line_count = 0

                        row = next(csv_reader)
                        bs_x = float(row['x'])
                        bs_y = float(row['y'])
                        bs_r = float(row['r'])

                    #    row = next(csv_reader)
                    #    due_x = float(row['x'])
                    #    due_y = float(row['y'])
                    #    due_r = float(row['r'])

                        for row in csv_reader:
                            ue_x.append( float(row['x']) )
                            ue_y.append( float(row['y']) )
                            line_count += 1

                        plt.scatter(ue_x, ue_y, color=colors[i], alpha=0.2)
                        plt.scatter([bs_x], [bs_y], color="purple")
                        plt.a_nnotate('Base station', (bs_x+5, bs_y+5) )
                        bs_circle = plt.Circle((bs_x, bs_y), bs_r, color=colors[i], alpha=0.2)
                        ax.add_artist(bs_circle)


    ue_x = []
    ue_y = []

    filename = 'nc_ues_positions.csv'
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

            plt.scatter(ue_x, ue_y, color="black", alpha=0.2)


    plt.scatter([due_x], [due_y], color="blue")
    plt.a_nnotate('DUE', (due_x+5, due_y+5) )
    due_circle = plt.Circle((due_x, due_y), due_r, color='blue', alpha=0.2)
    ax.add_artist(due_circle)
    ax.set(xlabel='m', ylabel='m')
    ax.set_aspect('equal', 'datalim')
    plt.savefig('map.png', dpi = 300)


###############################################################################
# Main
###############################################################################

# Get arguments
y_axis_initials = ''
y_axis_label1 = ''
x_axis_initials = ''
x_axis_label0 = ''
x_axis_label1 = ''
if len(sys.argv):
    if sys.argv[1] == 'e2edr':
        y_axis_initials = 'e2edr'
        y_axis_label1 = 'End to end delivery ratio'
    else:
        y_axis_initials = 'e2ed'
        y_axis_label1 = 'End to end delay'

    if sys.argv[2] == 'tp':
        x_axis_initials = 'tp'
        x_axis_label0 = 'transmission_power'
        x_axis_label1 = 'Transmission power \ dBm'
    else:
        x_axis_initials = 'dc'
        x_axis_label0 = 'duty_cycle'
        x_axis_label1 = 'Duty cycle \ s'
else:
    print('No arguments.')
    sys.exit()

# no_ues_bs, no_ues_nc
params = get_params()

# plot e2edr and e2ed
plot_e2edr_e2ed(params)

# plot maps
plot_maps(params)


