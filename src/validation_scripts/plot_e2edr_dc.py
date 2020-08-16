import csv
import matplotlib.pyplot as plt
import numpy as np

maxedr_paper = [0.95, 0.97, 0.98, 0.98, 0.985]
mu = []
s_1 = []
s_0 = []
e_1 = []
e_0 = []
duty_cycle = []

# e2edr_maxedr_dc.csv
# TODO:e2edr_mineed_dc.csv

with open('e2edr_maxedr_dc.csv') as csv_file:
    csv_reader = csv.DictReader(csv_file)
    line_count = 0
    for row in csv_reader:
        duty_cycle.append( float(row['duty_cycle']) )
        mu.append( float(row['mu']) )
        s_1.append( float(row['mu']) + float(row['s']) )
        s_0.append( float(row['mu']) - float(row['s']) )
        e_1.append( float(row['mu']) + float(row['e']) )
        e_0.append( float(row['mu']) - float(row['e']) )
        line_count += 1

ax = plt.gca()
plt.plot(duty_cycle, maxedr_paper, color="black", linestyle="-", label='maxEDR, standard model')
plt.scatter(duty_cycle, maxedr_paper, color="black", marker="s", s=30)
plt.plot(duty_cycle, mu, color="gray", linestyle="--", label='maxEDR, current model')
plt.fill_between(duty_cycle, s_0, s_1, _alpha=.1)
plt.fill_between(duty_cycle, e_0, e_1, color="red", _alpha=.1)
plt.scatter(duty_cycle, mu, color="gray", marker="s", s=30)
plt.legend(loc='lower right')
plt.ylim(0.85, 1.1)
ax.set(xlabel='Duty cycle', ylabel='End-to-end delivery ratio')

plt.savefig('e2edr_dc.jpg', dpi = 300)

