import matplotlib.pyplot as plt
import numpy as np

x = np.arange(0., 10., 0.1)
sinr_db = 10**( x / 10 )
erfc = np.exp( - sinr_db) / np.sqrt(4*3.1415*sinr_db)
plt.plot( x, erfc)
plt.yscale('log')
plt.xlabel('SINR \ dB')
plt.ylabel('erfc( sqrt( 10**( SINR / 10 ) ) )')
plt.show()

#sinr_db = 10**( 6.5 / 10 )
#erfc = np.exp( - sinr_db) / np.sqrt(4*3.1415*sinr_db)
#print(erfc)
