#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include <bits/stdc++.h>
#define Point pair<long long int, long long int>
using namespace std;

class ConvexHull{
    protected:
    /**
     * @brief contains the input points in a vector
     * 
     */
        vector<Point > input_points;
        vector<Point > output_hull;
        vector<map<Point, vector<int> > > sate_history;
    public:
        void readFile(string file_path);
        void setInput(vector<Point > input);
        vector<Point > getInputPoints();
        vector<Point > getOutput();
        void computeHull(string algo_name);
};

#endif