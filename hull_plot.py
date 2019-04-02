import matplotlib.pyplot as plt
import numpy as np


inp_points = np.loadtxt(fname="input_1.txt",skiprows=0)
# print(inp_points)
x = []
y = []
for point in inp_points:
    x.append(point[0])
    y.append(point[1])
plt.scatter(x,y,edgecolors="lightblue")

out_points = np.loadtxt(fname="output_kps.txt")
# print(out_points)
x = []
y = []
for point in out_points:
    x.append(point[0])
    y.append(point[1])
plt.scatter(x,y,edgecolors="red")
plt.plot(x,y,color="orange")
plt.show()