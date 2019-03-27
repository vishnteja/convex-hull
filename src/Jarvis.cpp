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

int orientation(Point p, Point q, Point r) 
{ 
    int val = (q.get_y() - p.get_y()) * (r.get_x() - q.get_x()) - 
              (q.get_x() - p.get_x()) * (r.get_y() - q.get_y()); 
  
    if (val == 0) return 0;  // colinear 
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 
  
void Jarvis(vector<Point> &points, int n) 
{ 

    if (n < 3) return; 
    vector<Point> hull; 

    int l = 0; 
    for (int i = 1; i < n; i++) 
        if (points[i].get_x() < points[l].get_x()) 
            l = i; 

    int p = l, q; 
    do
    { 
        hull.push_back(points[p]); 
        q = (p+1)%n; 
        for (int i = 0; i < n; i++) 
        { 
           if (orientation(points[p], points[i], points[q]) == 2) 
               q = i; 
        } 
        p = q; 
 
    } while (p != l);  

    for (int i = 0; i < hull.size(); i++) 
        cout << "(" << hull[i].get_x() << ", "
              << hull[i].get_y() << ")\n"; 
} 
 
int main() 
{ 
    vector<Point> points{{0, 3}, {2, 2}, {1, 1}, {2, 1}, 
                      {3, 0}, {0, 0}, {3, 3}}; 
    int n = points.size();
    Jarvis(points, n); 
    return 0; 
} 