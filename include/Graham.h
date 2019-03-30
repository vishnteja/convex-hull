#ifndef GRAHAM_H
#define GRAHAM_H

#include <bits/stdc++.h>
#include "ConvexHull.h"
#define Point pair<int, int>
using namespace std;

class Graham: public ConvexHull{
    public:
        void computeHull();
};

#endif