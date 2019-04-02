from random import randint
import random
from shapely.geometry import Polygon, Point, LineString
import math

def random_points(poly, num_points):
    min_x, min_y, max_x, max_y = poly.bounds
    points = []
    while len(points) < num_points :
        random_point = Point([random.uniform(min_x, max_x), random.uniform(min_y, max_y)])
        if(random_point.within(poly)):
            points.append(random_point)

    return points

def unique(points):
    final = list(set(tuple(p) for p in points))
    return final

def write_(final, file_path):
    with open("./test/"+file_path+".txt", "w") as f:
        for i in range(0, len(final)):
            f.write(("%s %s\n")%(final[i][0],final[i][1]))

import math, random

def generatePolygon( ctrX, ctrY, aveRadius, irregularity, spikeyness, numVerts ) :
    '''Start with the centre of the polygon at ctrX, ctrY, 
    then creates the polygon by sampling points on a circle around the centre. 
    Randon noise is added by varying the angular spacing between sequential points,
    and by varying the radial distance of each point from the centre.

    Params:
    ctrX, ctrY - coordinates of the "centre" of the polygon
    aveRadius - in px, the average radius of this polygon, this roughly controls how large the polygon is, really only useful for order of magnitude.
    irregularity - [0,1] indicating how much variance there is in the angular spacing of vertices. [0,1] will map to [0, 2pi/numberOfVerts]
    spikeyness - [0,1] indicating how much variance there is in each vertex from the circle of radius aveRadius. [0,1] will map to [0, aveRadius]
    numVerts - self-explanatory

    Returns a list of vertices, in CCW order.
    '''

    irregularity = clip( irregularity, 0,1 ) * 2*math.pi / numVerts
    spikeyness = clip( spikeyness, 0,1 ) * aveRadius

    # generate n angle steps
    angleSteps = []
    lower = (2*math.pi / numVerts) - irregularity
    upper = (2*math.pi / numVerts) + irregularity
    sum = 0
    for i in range(numVerts) :
        tmp = random.uniform(lower, upper)
        angleSteps.append( tmp )
        sum = sum + tmp

    # normalize the steps so that point 0 and point n+1 are the same
    k = sum / (2*math.pi)
    for i in range(numVerts) :
        angleSteps[i] = angleSteps[i] / k

    # now generate the points
    points = []
    angle = random.uniform(0, 2*math.pi)
    for i in range(numVerts) :
        r_i = clip( random.gauss(aveRadius, spikeyness), 0, 2*aveRadius )
        x = ctrX + r_i*math.cos(angle)
        y = ctrY + r_i*math.sin(angle)
        points.append( (int(x),int(y)) )

        angle = angle + angleSteps[i]

    return points

def clip(x, min, max) :
     if( min > max ) :  return x    
     elif( x < min ) :  return min
     elif( x > max ) :  return max
     else :             return x

N = 90000
points = generatePolygon(100000, 100000, 99000, 0, 0, N)
points = unique(points)
write_(points, "Ntest"+str(N))



# N = 1000000
# points = []
# for i in range(0, N):
#     points.append([randint(1, N*10000), randint(1, N*10000)])

