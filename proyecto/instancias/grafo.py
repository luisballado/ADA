import numpy as np
import matplotlib.pyplot as plt
import networkx as nx

#G = nx.Graph()

"""
n = 10
m = 10
pos = {(i,j): np.array([i,j]) for i in range(n) for j in range(m)}
nx.draw(G, pos, with_labels=True)
plt.show()
"""

G = nx.grid_2d_graph(1000,1000)
pos = {(i,j): np.array([i,j]) for i in range(1000) for j in range(1000)}
nx.draw(G, pos, with_labels=True)

plt.show()
