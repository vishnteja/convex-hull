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
plt.show()