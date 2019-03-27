#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include <bits/stdc++.h>
#define Point pair<int, int>
using namespace std;

class ConvexHull{
    protected:
    /**
     * @brief contains the input points in a vector
     * 
     */
        vector<Point > input_points;
        vector<Point > output_hull;
    public:
        void readFile(string file_path);
        vector<Point > getInputPoints();
        vector<Point > getOutput();
};

#endif