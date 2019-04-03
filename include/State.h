#ifndef STATE_H
#define STATE_H

#include <bits/stdc++.h>
#define Point pair<long long int, long long int>
using namespace std;

class State{
    public:
        vector<Point > normal_points;
        vector<Point > bold_points;
        vector<Point > normal_edges;
        vector<Point > bold_edges;
        State(vector<Point > NP,vector<Point > BP, vector<Point > NE,vector<Point > BE);
        State();
        vector<Point > getNormalP();
        vector<Point > getBoldP();
        vector<Point > getNormalE();
        vector<Point > getBoldE();
};

#endif
