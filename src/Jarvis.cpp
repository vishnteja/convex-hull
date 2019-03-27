#include "Jarvis.h" 
#define Point pair<int,int>
using namespace std; 

/**
 * @brief To find orientation of ordered triplet (p, q, r).
 *         
 * @param p First Point
 * @param q Second Point
 * @param r Third Point
 * @return int The function returns following values 
 *             0 --> p, q and r are colinear 
 *             1 --> Clockwise 
 *             2 --> Counterclockwise
 */
int orientation(Point p, Point q, Point r) 
{ 
    int val = (q.second - p.second) * (r.first - q.first) - 
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
           if (orientation(input_points[p], input_points[i], input_points[q]) == 2) 
               q = i; 
        } 
        p = q; 
 
    } while (p != l);  

    // for (int i = 0; i < output_hull.size(); i++) 
    //     cout << "(" << output_hull[i].first << ", "
    //           << output_hull[i].second << ")\n"; 
}  