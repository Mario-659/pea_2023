import networkx as nx
import matplotlib.pyplot as plt

distance_matrix = [
    [0, 20, 30, 31, 28, 40],
    [30, 0, 10, 14, 20, 44],
    [40, 20, 0, 10, 22, 50],
    [41, 24, 20, 0, 14, 42],
    [38, 30, 32, 24, 0, 28],
    [50, 54, 60, 52, 38, 0]
]


G = nx.Graph()

n = len(distance_matrix)
for i in range(n):
    for j in range(i + 1, n):  # since it's undirected, only add one way
        G.add_edge(i, j, weight=distance_matrix[i][j])
        G.add_edge(j, i, weight=distance_matrix[j][i])


pos = nx.spring_layout(G)  # layout for positioning nodes
edge_labels = nx.get_edge_attributes(G, 'weight')


plt.figure(figsize=(8, 6))
nx.draw(G, pos, with_labels=True, node_color='lightblue', node_size=500, font_size=10)
nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)
plt.title("Graph Representation of TSP Distance Matrix")
plt.show()
