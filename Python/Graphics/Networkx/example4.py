import networkx as nx
import matplotlib.pyplot as plt

# BA scale-free degree network
# generalize BA network which has 20 nodes, m = 1
BA = nx.random_graphs.barabasi_albert_graph(20, 1)
# spring layout
pos = nx.spring_layout(BA)
nx.draw(BA, pos, with_labels = False, node_size = 30)
# nx.draw(BA,pos)
plt.show()