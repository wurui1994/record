import networkx as nx
import matplotlib.pyplot as plt

# regular graphy
# generate a regular graph which has 20 nodes & each node has 3 neghbour nodes.
RG = nx.random_graphs.random_regular_graph(3, 20)
# the spectral layout
pos = nx.spectral_layout(RG)
# draw the regular graphy
nx.draw(RG, pos, with_labels = False, node_size = 30)
plt.show()