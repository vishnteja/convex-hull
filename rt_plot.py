import matplotlib.pyplot as plt
import numpy as np
import scipy.optimize as opt

def func(x, a, b, c):
    return a*np.exp(-b*x) + c

inp_points = np.loadtxt(fname="RunningTime.txt")
print(inp_points)
x = inp_points[:, 0]
y = inp_points[:, 1]
plt.plot(x, y, label="Jarvis")
plt.scatter(x, y)
y = inp_points[:, 2]    
plt.plot(x, y, label="Graham")
plt.scatter(x, y)
y = inp_points[:, 3]
plt.plot(x, y, label="KPS")
plt.scatter(x, y)
plt.xlabel("n*h")
plt.ylabel("Time (s)")

# optimizedParameters, pcov = opt.curve_fit(func, x, y)

# plt.plot(x, func(x, *optimizedParameters), label="fit")
plt.savefig('NH_Jarvis.png')
plt.legend()
plt.show()
# x = []
# y = []
# for point in inp_points:
#     x.append(point[0])
#     y.append(point[1])
# plt.scatter(x,y,edgecolors="lightblue")
