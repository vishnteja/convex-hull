#ifndef STATE_H
#define STATE_H

#include <bits/stdc++.h>
#include "Segment.h"
#include "ConvexHull.h"
#define Point pair<int, int>
using namespace std;

class State: public ConvexHull{
    protected:
        map<Point, vector<int> > state_table;
    public:
        State();
        void storeState(vector<Point > points, vector<Segment > edges);
        map<Point, vector<int> > getState();
};

#endif