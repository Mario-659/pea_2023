import matplotlib.pyplot as plt
import numpy as np
import pandas

d_File = pandas.read_csv('dijkstra.csv', header=None)
b_file = pandas.read_csv('belmann.csv', header=None)

d_matrix = d_File[d_File[2]=='matrix']
d_list = d_File[d_File[2]=='list']

b_matrix = b_file[b_file[2]=='matrix']
b_list = b_file[b_file[2]=='list']

d_matrix_20 = d_matrix[d_matrix[1]==20].to_numpy()
d_matrix_60 = d_matrix[d_matrix[1]==60].to_numpy()
d_matrix_99 = d_matrix[d_matrix[1]==99].to_numpy()

d_list_20 = d_list[d_list[1]==20].to_numpy()
d_list_60 = d_list[d_list[1]==60].to_numpy()
d_list_99 = d_list[d_list[1]==99].to_numpy()

b_matrix_20 = b_matrix[b_matrix[1]==20].to_numpy()
b_matrix_60 = b_matrix[b_matrix[1]==60].to_numpy()
b_matrix_99 = b_matrix[b_matrix[1]==99].to_numpy()

b_list_20 = b_list[b_list[1]==20].to_numpy()
b_list_60 = b_list[b_list[1]==60].to_numpy()
b_list_99 = b_list[b_list[1]==99].to_numpy()

plt.plot(d_matrix_20[:,0], d_matrix_20[:,3], label='Dijkstra - macierz')
plt.scatter(d_matrix_20[:,0], d_matrix_20[:,3])
plt.plot(d_list_20[:,0], d_list_20[:,3], label='Dijkstra - lista')
plt.scatter(d_list_20[:,0], d_list_20[:,3])
plt.plot(b_matrix_20[:,0], b_matrix_20[:,3], label='Bellman Ford - macierz')
plt.scatter(b_matrix_20[:,0], b_matrix_20[:,3])
plt.plot(b_list_20[:,0], b_list_20[:,3], label='Bellman Ford - lista')
plt.scatter(b_list_20[:,0], b_list_20[:,3])
plt.legend()
plt.title("Gęstość = 20%")
plt.ylabel('czas [s]')
plt.xlabel('Liczba wierzchołków')
plt.savefig("20densSP.png", dpi=800)
plt.clf()

plt.plot(d_matrix_60[:,0], d_matrix_60[:,3], label='Dijkstra - macierz')
plt.scatter(d_matrix_60[:,0], d_matrix_60[:,3])
plt.plot(d_list_60[:,0], d_list_60[:,3], label='Dijkstra - lista')
plt.scatter(d_list_60[:,0], d_list_60[:,3])
plt.plot(b_matrix_60[:,0], b_matrix_60[:,3], label='Bellman Ford - macierz')
plt.scatter(b_matrix_60[:,0], b_matrix_60[:,3])
plt.plot(b_list_60[:,0], b_list_60[:,3], label='Bellman Ford - lista')
plt.scatter(b_list_60[:,0], b_list_60[:,3])
plt.legend()
plt.title("Gęstość = 60%")
plt.ylabel('czas [s]')
plt.xlabel('Liczba wierzchołków')
plt.savefig("60densSP.png", dpi=800)
plt.clf()


plt.plot(d_matrix_99[:,0], d_matrix_99[:,3], label='Dijkstra - macierz')
plt.scatter(d_matrix_99[:,0], d_matrix_99[:,3])
plt.plot(d_list_99[:,0], d_list_99[:,3], label='Dijkstra - lista')
plt.scatter(d_list_99[:,0], d_list_99[:,3])
plt.plot(b_matrix_99[:,0], b_matrix_99[:,3], label='Bellman Ford - macierz')
plt.scatter(b_matrix_99[:,0], b_matrix_99[:,3])
plt.plot(b_list_99[:,0], b_list_99[:,3], label='Bellman Ford - lista')
plt.scatter(b_list_99[:,0], b_list_99[:,3])
plt.legend()
plt.title("Gęstość = 99%")
plt.ylabel('czas [s]')
plt.xlabel('Liczba wierzchołków')
plt.savefig("99densSP.png", dpi=800)
plt.clf()
