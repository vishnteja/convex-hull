#include "../include/Jarvis.h"
using namespace std; 
 
int orientationJ(Point p, Point q, Point r){
    long long int val = (q.second - p.second) * (r.first - q.first) - 
              (q.first - p.first) * (r.second - q.second); 
  
    if (val == 0) return 0;  // colinear 
    return (val > 0)? 1: 2; // clock or counterclock wise 
}

/**
 * @brief computes convex hull stores in output_hull
 * computes convex hull as described in Jarvis March Algorithm
 */
void Jarvis::computeHull()
{
    clock_t start, end;
    double cpu_time;
    start = clock();
    int n = input_points.size();    
    if (n < 3) return; 

    int l = 0; 
    for (int i = 1; i < n; i++) 
        if (input_points[i].first < input_points[l].first) 
            l = i; 

    int p = l, q; 
    do
    { 
        output_hull.push_back(input_points[p]); 
        q = (p+1)%n; 
        for (int i = 0; i < n; i++) 
        { 
            if (orientationJ(input_points[p], input_points[i], input_points[q]) == 2) 
               q = i; 
        } 
        p = q; 
 
    } while (p != l);

    end = clock();
    cpu_time = double(end - start) / double(CLOCKS_PER_SEC);
    cout<<"Time: "<<fixed<<cpu_time<<setprecision(6);
    cout<< " s" << endl;
    // for (int i = 0; i < output_hull.size(); i++) 
    //     cout << "(" << output_hull[i].first << ", "
    //           << output_hull[i].second << ")\n"; 
}  