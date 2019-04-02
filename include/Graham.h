#ifndef GRAHAM_H
#define GRAHAM_H

#include <bits/stdc++.h>
#include "ConvexHull.h"
using namespace std;

class Graham: public ConvexHull{
    public:
        void computeHull();
};

#endif