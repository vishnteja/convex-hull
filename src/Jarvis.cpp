#include "Jarvis.h"
#include "Segment.h" 
using namespace std; 
 
/**
 * @brief computes convex hull stores in output_hull
 * computes convex hull as described in Jarvis March Algorithm
 */
void Jarvis::computeHull()
{
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
            Segment seg = Segment(input_points[p], input_points[i]);
            if (seg.orientation(input_points[q]) == -1) 
               q = i; 
        } 
        p = q; 
 
    } while (p != l);  

    // for (int i = 0; i < output_hull.size(); i++) 
    //     cout << "(" << output_hull[i].first << ", "
    //           << output_hull[i].second << ")\n"; 
}  