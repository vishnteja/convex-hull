#include "../include/Graham.h"
using namespace std;   
 
Point p0(0,0); 

/**
 * @brief Finds next to top in a stack 
 * @param S Stack 
 * @return Point Next to top element
 */   
Point nextToTop(vector<Point> &S) 
{ 
    Point p = S.back(); 
    S.pop_back(); 
    Point res = S.back(); 
    S.push_back(p); 
    return res; 
} 

/**
 * @brief Swaps two points
 * @param p1 First point
 * @param p2 Second point
 */  
void swap(Point &p1, Point &p2) 
{ 
    Point temp = p1; 
    p1 = p2; 
    p2 = temp; 
} 

/**
 * @brief Finds the square distance between two points.
 *         
 * @param p1 First Point
 * @param p2 Second Point
 * @return int Squared Distance
 */
int distSq(Point p1, Point p2) 
{ 
    return (p1.first - p2.first)*(p1.first - p2.first) + 
          (p1.second - p2.second)*(p1.second - p2.second); 
} 

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
   long long int val = (q.second - p.second) * (r.first - q.first) - 
              (q.first - p.first) * (r.second - q.second); 
  
    if (val == 0) return 0;  // colinear 
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 

/**
 * @brief A function used by library function qsort() to sort an array of 
 * points with respect to the first point
 *         
 * @param vp1 Pointer to first element
 * @param vp2 Pointer to second element
 * @return int True or False
 */
int compare(const void *vp1, const void *vp2) 
{ 
   Point *p1 = (Point *)vp1; 
   Point *p2 = (Point *)vp2; 

   int o = orientation(p0, *p1, *p2); 
   if (o == 0) 
     return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1; 
  
   return (o == 2)? -1: 1; 
} 

/**
 * @brief computes convex hull stores in output_hull
 * computes convex hull as described in Graham Scan Algorithm
 */
void Graham::computeHull() 
{ 
   clock_t start, end;
   double cpu_time;
   start = clock();
   
   int n = input_points.size(); 
   int ymin = input_points[0].second, min = 0; 
   for (int i = 1; i < n; i++) 
   { 
     int y = input_points[i].second; 
     if ((y < ymin) || (ymin == y && input_points[i].first < input_points[min].first)) 
        ymin = input_points[i].second, min = i; 
   } 
   swap(input_points[0], input_points[min]); 
   p0 = input_points[0]; 
   qsort(&input_points[1], n-1, sizeof(Point), compare); 

   int m = 1; 
   for (int i=1; i<n; i++) 
   { 
       while (i < n-1 && orientation(p0, input_points[i], input_points[i+1]) == 0) 
          i++; 
  
       input_points[m] = input_points[i]; 
       m++;  
   } 
 
   if (m < 3) return; 
   output_hull.push_back(input_points[0]); 
   output_hull.push_back(input_points[1]); 
   output_hull.push_back(input_points[2]); 

   for (int i = 3; i < m; i++) 
   {
      while (orientation(nextToTop(output_hull), output_hull.back(), input_points[i]) != 2) 
         output_hull.pop_back(); 
      output_hull.push_back(input_points[i]); 
   } 
   end = clock();
   cpu_time = (double(end - start) / double(CLOCKS_PER_SEC));
   cout<<"Time: "<<fixed<<cpu_time<<setprecision(6);
   cout<< " s" << endl;


//    while (!output_hull.empty()) 
//    { 
//        Point p = output_hull.back(); 
//        cout << "(" << p.first << ", " << p.second <<")" << endl; 
//        output_hull.pop_back(); 
//    } 
} 