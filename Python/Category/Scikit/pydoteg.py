import pydot
edg = [(1,2), (1,3), (1,4) , (3,4)]
g=pydot.graph_from_edges(edg)
g.write_pdf('graph.pdf', prog = 'dot')