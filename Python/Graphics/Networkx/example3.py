import networkx as nx
import matplotlib.pyplot as plt

# WS network

# generate a WS network which has 20 nodes,
# each node has 4 neighbour nodes,
# random reconnection probability was 0.3.
WS = nx.random_graphs.watts_strogatz_graph(20, 4, 0.3)
# circular layout
pos = nx.circular_layout(WS)
nx.draw(WS, pos, with_labels = False, node_size = 30)
plt.show()