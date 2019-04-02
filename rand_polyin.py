import numpy as np
from random import randint
import random
from shapely.geometry import Polygon, Point, LineString
import math

def random_points(poly, num_points):
    min_x, min_y, max_x, max_y = poly.bounds
    points = []
    while len(points) < num_points :
        random_point = Point([randint(min_x, max_x), randint(min_y, max_y)])
        if(random_point.within(poly)):
            points.append(random_point)

    return points

def unique(points):
    final = list(set(tuple(p) for p in points))
    return final

def write_(final, file_path):
    with open("./test/"+file_path+".txt", "w") as f:
        for i in range(0, len(final)):
            f.write(("%d %d\n")%(final[i][0],final[i][1]))

out_points = np.loadtxt(fname="output_1.txt")
unique_out2 = set()
x = []
y = []
for point in out_points:
    unique_out2.add((point[0], point[1]))

poly = Polygon(list(unique_out2))
points = random_points(poly, 19000)

listarray = list(unique_out2)
for pp in points:
    listarray.append([int(pp.x), int(pp.y)])

unique_points = unique(listarray)
write_(unique_points, "plyT1000")

