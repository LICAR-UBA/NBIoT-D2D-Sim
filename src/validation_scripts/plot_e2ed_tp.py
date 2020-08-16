import csv
import matplotlib.pyplot as plt
import numpy as np

# mineed_paper = [0.88, 0.94, 0.948, 0.96, 0.975, 0.98, 0.985, 0.99]
maxedr_paper = [6.2, 5.1, 4.8, 4.9, 4.5, 4., 3.9, 3.8]
mu = []
s_1 = []
s_0 = []
e_1 = []
e_0 = []
transmission_power = []

# e2ed_maxedr_tp.csv
# TODO:e2ed_mineed_tp.csv

with open('e2ed_maxedr_tp.csv') as csv_file:
    csv_reader = csv.DictReader(csv_file)
    line_count = 0
    for row in csv_reader:
        transmission_power.append( float(row['transmission_power']) )
        mu.append( float(row['mu']) )
        s_1.append( float(row['mu']) + float(row['s']) )
        s_0.append( float(row['mu']) - float(row['s']) )
        e_1.append( float(row['mu']) + float(row['e']) )
        e_0.append( float(row['mu']) - float(row['e']) )
        line_count += 1

ax = plt.gca()
plt.plot(transmission_power, maxedr_paper, color="black", linestyle="-", label='maxEDR, standard model')
plt.scatter(transmission_power, maxedr_paper, color="black", marker="s", s=30)
plt.plot(transmission_power, mu, color="gray", linestyle="--", label='maxEDR, current model')
plt.fill_between(transmission_power, s_0, s_1, _alpha=.1)
plt.fill_between(transmission_power, e_0, e_1, color="red", _alpha=.1)
plt.scatter(transmission_power, mu, color="gray", marker="s", s=30)
plt.legend(loc='upper right')
plt.ylim(1, 15)
ax.set(xlabel='Transmission power \ dBm', ylabel='End-to-end delay')

plt.savefig('e2ed_tp.jpg', dpi = 300)




