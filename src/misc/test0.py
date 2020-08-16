import matplotlib.pyplot as plt
import numpy as np
import csv
from mpl_toolkits.mplot3d import Axes3D

from mpl_toolkits.mplot3d.axes3d import get_test_data

import matplotlib.cm as cm


#================
# Adquisicion de datos
#================

DataAll1D = np.loadtxt("data1.csv", delimiter=",")

RO_I = list(dict.fromkeys(DataAll1D[:,1]))
RO_E = list(dict.fromkeys(DataAll1D[:,2]))

n = len(RO_I)
m = len(RO_E)

# create 2d x,y grid (both X and Y will be 2d)
RO_I, RO_E = np.meshgrid(RO_I, RO_E)

EDR = np.array(DataAll1D[:,3]).reshape(n,m)

T_P = list(dict.fromkeys(DataAll1D[:,0]))
T_P = np.ones((n,m)) * T_P

T_P2 = T_P + 5


#===============
# Plot setup
#===============
fig = plt.figure(figsize=plt.figaspect(0.5))

cmap = plt.cm.OrRd

rows = 2

cols = 5

#===============
# 1 subplot
#===============

ax = fig.add_subplot(rows, cols, 1, projection='3d')

ax.plot_surface(RO_E,RO_I,T_P, facecolors=cmap(EDR), shade=False, alpha=0.7)
ax.plot_surface(RO_E,RO_I,T_P, rstride=1, cstride=1, alpha=0, linewidth=0.5, edgecolors='k')

ax.plot_surface(RO_E,RO_I,T_P2, facecolors=cmap(EDR), shade=False, alpha=0.7)
ax.plot_surface(RO_E,RO_I,T_P2, rstride=1, cstride=1, alpha=0, linewidth=0.5, edgecolors='k')


#===============
# 2 subplot
#===============

ax = fig.add_subplot(rows, cols, 2, projection='3d')

ax.plot_surface(RO_E,RO_I,T_P, facecolors=cmap(EDR), shade=False, alpha=0.7)
ax.plot_surface(RO_E,RO_I,T_P, rstride=1, cstride=1, alpha=0, linewidth=0.5, edgecolors='k')

ax.plot_surface(RO_E,RO_I,T_P2, facecolors=cmap(EDR), shade=False, alpha=0.7)
ax.plot_surface(RO_E,RO_I,T_P2, rstride=1, cstride=1, alpha=0, linewidth=0.5, edgecolors='k')


#===============
# 3 subplot
#===============

ax = fig.add_subplot(rows, cols, 3, projection='3d')

ax.plot_surface(RO_E,RO_I,T_P, facecolors=cmap(EDR), shade=False, alpha=0.7)
ax.plot_surface(RO_E,RO_I,T_P, rstride=1, cstride=1, alpha=0, linewidth=0.5, edgecolors='k')

ax.plot_surface(RO_E,RO_I,T_P2, facecolors=cmap(EDR), shade=False, alpha=0.7)
ax.plot_surface(RO_E,RO_I,T_P2, rstride=1, cstride=1, alpha=0, linewidth=0.5, edgecolors='k')


#===============
# 4 subplot
#===============

ax = fig.add_subplot(rows, cols, 4, projection='3d')

ax.plot_surface(RO_E,RO_I,T_P, facecolors=cmap(EDR), shade=False, alpha=0.7)
ax.plot_surface(RO_E,RO_I,T_P, rstride=1, cstride=1, alpha=0, linewidth=0.5, edgecolors='k')

ax.plot_surface(RO_E,RO_I,T_P2, facecolors=cmap(EDR), shade=False, alpha=0.7)
ax.plot_surface(RO_E,RO_I,T_P2, rstride=1, cstride=1, alpha=0, linewidth=0.5, edgecolors='k')


#===============
# 5 subplot
#===============

ax = fig.add_subplot(rows, cols, 5, projection='3d')

ax.plot_surface(RO_E,RO_I,T_P, facecolors=cmap(EDR), shade=False, alpha=0.7)
ax.plot_surface(RO_E,RO_I,T_P, rstride=1, cstride=1, alpha=0, linewidth=0.5, edgecolors='k')

ax.plot_surface(RO_E,RO_I,T_P2, facecolors=cmap(EDR), shade=False, alpha=0.7)
ax.plot_surface(RO_E,RO_I,T_P2, rstride=1, cstride=1, alpha=0, linewidth=0.5, edgecolors='k')


#===============
# 6 subplot
#===============

ax = fig.add_subplot(rows, cols, 6, projection='3d')

ax.plot_surface(RO_E,RO_I,T_P, facecolors=cmap(EDR), shade=False, alpha=0.7)
ax.plot_surface(RO_E,RO_I,T_P, rstride=1, cstride=1, alpha=0, linewidth=0.5, edgecolors='k')

ax.plot_surface(RO_E,RO_I,T_P2, facecolors=cmap(EDR), shade=False, alpha=0.7)
ax.plot_surface(RO_E,RO_I,T_P2, rstride=1, cstride=1, alpha=0, linewidth=0.5, edgecolors='k')



#===============
# 7 subplot
#===============

ax = fig.add_subplot(rows, cols, 7, projection='3d')

ax.plot_surface(RO_E,RO_I,T_P, facecolors=cmap(EDR), shade=False, alpha=0.7)
ax.plot_surface(RO_E,RO_I,T_P, rstride=1, cstride=1, alpha=0, linewidth=0.5, edgecolors='k')

ax.plot_surface(RO_E,RO_I,T_P2, facecolors=cmap(EDR), shade=False, alpha=0.7)
ax.plot_surface(RO_E,RO_I,T_P2, rstride=1, cstride=1, alpha=0, linewidth=0.5, edgecolors='k')


#===============
# 8 subplot
#===============

ax = fig.add_subplot(rows, cols, 8, projection='3d')

ax.plot_surface(RO_E,RO_I,T_P, facecolors=cmap(EDR), shade=False, alpha=0.7)
ax.plot_surface(RO_E,RO_I,T_P, rstride=1, cstride=1, alpha=0, linewidth=0.5, edgecolors='k')

ax.plot_surface(RO_E,RO_I,T_P2, facecolors=cmap(EDR), shade=False, alpha=0.7)
ax.plot_surface(RO_E,RO_I,T_P2, rstride=1, cstride=1, alpha=0, linewidth=0.5, edgecolors='k')

#===============
# 9 subplot
#===============

ax = fig.add_subplot(rows, cols, 9, projection='3d')

ax.plot_surface(RO_E,RO_I,T_P, facecolors=cmap(EDR), shade=False, alpha=0.7)
ax.plot_surface(RO_E,RO_I,T_P, rstride=1, cstride=1, alpha=0, linewidth=0.5, edgecolors='k')

ax.plot_surface(RO_E,RO_I,T_P2, facecolors=cmap(EDR), shade=False, alpha=0.7)
ax.plot_surface(RO_E,RO_I,T_P2, rstride=1, cstride=1, alpha=0, linewidth=0.5, edgecolors='k')

ax = fig.add_subplot(rows, cols, 10, visible=False)


x = np.arange(2)

m = cm.ScalarMappable()
m.set_array(x)
m.set_cmap(cmap)

plt.colorbar(m)



plt.show()
