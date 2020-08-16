import matplotlib.pyplot as plt
from scipy import special
import numpy as np


# Parameters

sinr_min = -16
sinr_max = 6
nrep = 128
TBS = 96
BLER = 0.35
px_db = 6
noise_db = -118
delta_max = 17
delta_min = 0
delta_sinr = ( delta_max - delta_min ) / 4
alpha = 3.7


# Script

sinr_db = np.arange(sinr_min, sinr_max, 0.1)

styles = [':','-.','--','-',':','-.','--','-',':','-.','--','-']

fig = plt.figure()
ax1 = plt.subplot(1,1,1)

deltas = list(np.arange(delta_max,delta_min,-delta_sinr)) + [0]
for i,d in enumerate(deltas):
    sinr_eff_db = sinr_db + d
    sinr_eff = 10**( sinr_eff_db / 10 )
    x = np.sqrt( sinr_eff / 2 )
    erfc = special.erfc(x)
    ber = 0.5 * erfc
    bler = np.power((1 - np.power(1 - ber, TBS)),nrep)
    ax1.plot( sinr_db, bler, color='red', linestyle=styles[i], label='$\delta$ = '+str(d)+" dBm")

bler_line = len(sinr_db) * [ BLER ]
ax1.plot( sinr_db, bler_line, linestyle='--', color='gray', label='BLER = ' + str(BLER))
ax1.set_yscale('log')
ax1.set_ylim((0.00001, 1.2))
ax1.set_xlabel('$\mathregular{SINR^{eff}}$ \ dB')
ax1.set_ylabel('BLER')
plt.legend(loc='lower left')
ax2 = ax1.twiny()
ax2.set_xlabel('r \ km')
sinr_db_ticks = np.arange(sinr_min, sinr_max +  1, 4)
px = 10**( px_db / 10)
noise = 10**( noise_db / 10)
sinr_ticks = np.power(10, sinr_db_ticks / 10)
distances = np.power( px / ( noise * sinr_ticks  ), 1/alpha ) / 1000
distances = np.around(distances, decimals=2)
ax2.set_xlim(ax1.get_xlim())
ax1.set_xticks(sinr_db_ticks)
ax1.set_xticklabels(sinr_db_ticks)
ax2.set_xticks(sinr_db_ticks)
ax2.set_xticklabels(distances)

plt.show()

