#include "Segment.h"
#include <bits/stdc++.h>
#define Point pair<int, int>
using namespace std;

/**
 * @brief Construct a new Segment:: Segment object
 * 
 */
Segment::Segment(){}

/**
 * @brief Construct a new Segment with a, b as endpoints
 * 
 * @param a Point
 * @param b Point
 */
Segment::Segment(Point a, Point b){
    if(a.first < b.first){
        p1 = a;
        p2 = b;
    }else{
        p1 = b;
        p2 = a;
    }
}

/**
 * @brief Returns left point with respect to x-axis
 * 
 * @return Point 
 */
Point Segment::getP1(){
    return p1;
}

/**
 * @brief Returns right point with respect to x-axis
 * 
 * @return Point 
 */
Point Segment::getP2(){
    return p2;
}

/**
 * @brief Calculates slope of the segment
 * 
 * if it does not exisr (x-coordinate is the same) then returns 0
 * @return double slope value
 */
double Segment::slope(){
    if(p1.first == p2.first)
        return 0;
    else
        return (double)(p2.second-p1.second)/(p2.first-p1.first);
}

/**
 * @brief Checks orientation with respect to the segment
 * 
 * @param c Point to check orientation
 * @return int 
 */
int Segment::orientation(Point c){
    int res = (p2.second-p1.second)*(c.first-p2.first) - (c.second-p2.second)*(p2.first-p1.first); 
    if (res == 0) 
        return 0; 
    if (res > 0) 
        return 1; 
    return -1; 
}