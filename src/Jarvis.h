#ifndef JARVIS_H
#define JARVIS_H

#include <bits/stdc++.h>
#include "ConvexHull.h"
#define Point pair<int, int>
using namespace std;

class Jarvis: public ConvexHull{
    public:
        void computeHull();
};

#endif