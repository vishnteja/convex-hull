#ifndef ULTIMATE_H
#define ULTIMATE_H

#include <bits/stdc++.h>
#include "ConvexHull.h"
#include "Segment.h"
using namespace std;

class Ultimate: public ConvexHull{
    public:
        Ultimate();
        Ultimate(string file_path);
        void computeHull();
        vector<Point > computeUpperHull();
        vector<Point > computeLowerHull();
        vector<Point > upperHull(Point pmin, Point pmax, vector<Point > T);
        Segment upperBridge(vector<Point > S, double x_median);
        vector<Point > lowerHull(Point pmin, Point pmax, vector<Point > T);
        Segment lowerBridge(vector<Point > S, double x_median);
        double medianX(vector<Point > T);
        void storeState(vector<Point > points, vector<Segment > edges);
        void initMap();
};

#endif
