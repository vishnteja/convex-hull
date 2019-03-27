#include <bits/stdc++.h> 
using namespace std; 
  
class Point 
{ 
    float x, y;
    public:
    
    Point(float x, float y){
        this->x = x;
        this->y = y;
    }
    float get_x(){return x;}
    float get_y(){return y;}
    void set_x(float x){this->x = x;}
    void set_y(float y){this->y = y;}
}; 
 
Point p0(0,0); 
  
Point nextToTop(stack<Point> &S) 
{ 
    Point p = S.top(); 
    S.pop(); 
    Point res = S.top(); 
    S.push(p); 
    return res; 
} 
  
int swap(Point &p1, Point &p2) 
{ 
    Point temp = p1; 
    p1 = p2; 
    p2 = temp; 
} 

int distSq(Point p1, Point p2) 
{ 
    return (p1.get_x() - p2.get_x())*(p1.get_x() - p2.get_x()) + 
          (p1.get_y() - p2.get_y())*(p1.get_y() - p2.get_y()); 
} 
  
int orientation(Point p, Point q, Point r) 
{ 
    int val = (q.get_y() - p.get_y()) * (r.get_x() - q.get_x()) - 
              (q.get_x() - p.get_x()) * (r.get_y() - q.get_y()); 
  
    if (val == 0) return 0;  // colinear 
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 

int compare(const void *vp1, const void *vp2) 
{ 
   Point *p1 = (Point *)vp1; 
   Point *p2 = (Point *)vp2; 

   int o = orientation(p0, *p1, *p2); 
   if (o == 0) 
     return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1; 
  
   return (o == 2)? -1: 1; 
} 

void convexHull(vector<Point> &points, int n) 
{ 
   int ymin = points[0].get_y(), min = 0; 
   for (int i = 1; i < n; i++) 
   { 
     int y = points[i].get_y(); 
     if ((y < ymin) || (ymin == y && points[i].get_x() < points[min].get_x())) 
        ymin = points[i].get_y(), min = i; 
   } 
   swap(points[0], points[min]); 
   p0 = points[0]; 
   qsort(&points[1], n-1, sizeof(Point), compare); 

   int m = 1; 
   for (int i=1; i<n; i++) 
   { 
       while (i < n-1 && orientation(p0, points[i], points[i+1]) == 0) 
          i++; 
  
       points[m] = points[i]; 
       m++;  
   } 
 
   if (m < 3) return; 
   stack<Point> S; 
   S.push(points[0]); 
   S.push(points[1]); 
   S.push(points[2]); 

   for (int i = 3; i < m; i++) 
   {
      while (orientation(nextToTop(S), S.top(), points[i]) != 2) 
         S.pop(); 
      S.push(points[i]); 
   } 

   while (!S.empty()) 
   { 
       Point p = S.top(); 
       cout << "(" << p.get_x() << ", " << p.get_y() <<")" << endl; 
       S.pop(); 
   } 
} 

int main() 
{ 
   vector<Point> points{{0, 3}, {1, 1}, {2, 2}, {4, 4}, 
                      {0, 0}, {1, 2}, {3, 1}, {3, 3}}; 
    int n = points.size();
    convexHull(points, n); 
    return 0; 
}