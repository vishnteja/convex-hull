#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include <bits/stdc++.h>
#define Point pair<long long int, long long int>
#include "State.h"
using namespace std;

class ConvexHull{
    protected:
    /**
     * @brief contains the input points in a vector
     *
     */
        vector<Point > input_points;
        vector<Point > output_hull;
        vector<State > history;
    public:
        bool verbose;
        void readFile(string file_path);
        void setInput(vector<Point > input);
        vector<Point > getInputPoints();
        vector<Point > getOutput();
        vector<State > computeHull(string algo_name);
        vector<State > getHistory();
        void setHistory(vector<State >);
};

#endif
