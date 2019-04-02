#ifndef SEGMENT_H
#define SEGMENT_H

#include <bits/stdc++.h>
#define Point pair<long long int, long long int>
using namespace std;

class Segment{
    private:
        Point p1;
        Point p2;
    public:
        Segment();
        Segment(Point a, Point b);
        Point getP1();
        Point getP2();
        double slope();
        int orientation(Point c);
};

#endif