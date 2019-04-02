#include <iostream> 
#include <bits/stdc++.h>
using namespace std; 
  
// Define Infinite (Using INT_MAX caused overflow problems) 
#define INF 10000 
typedef struct Point 
{ 
    long long int x; 
    long long int y; 
}Point; 

vector<Point > points;

void readFile(string file_path){
    // Note:- Points have to positive integers
    // Read Inputs
    ifstream input_file;
    input_file.open(file_path);

    // Store points in a vector

    string str;
    while (getline(input_file, str)){
        // Convert string to char * for strtok
        int n = str.length();
        char array[n+1];
        strcpy(array, str.c_str());

        // Get the X and Y tokens
        char* token1 = strtok(array, " ");
        string x1(token1);
        char* token2 = strtok(NULL, " ");
        string y1(token2);

        // Conver string to long int
        long long x = stoll(x1);
        long long y = stoll(y1);

        points.push_back({x, y});
    }
}

// Given three colinear points p, q, r, the function checks if 
// point q lies on line segment 'pr' 
bool onSegment(Point p, Point q, Point r) 
{ 
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && 
            q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) 
        return true; 
    return false; 
} 
  
// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(Point p, Point q, Point r) 
{ 
    long long int val = (q.y - p.y) * (r.x - q.x) - 
              (q.x - p.x) * (r.y - q.y); 
  
    if (val == 0) return 0;  // colinear 
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 
  
// The function that returns true if line segment 'p1q1' 
// and 'p2q2' intersect. 
bool doIntersect(Point p1, Point q1, Point p2, Point q2) 
{ 
    // Find the four orientations needed for general and 
    // special cases 
    int o1 = orientation(p1, q1, p2); 
    int o2 = orientation(p1, q1, q2); 
    int o3 = orientation(p2, q2, p1); 
    int o4 = orientation(p2, q2, q1); 
  
    // General case 
    if (o1 != o2 && o3 != o4) 
        return true; 
  
    // Special Cases 
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1 
    if (o1 == 0 && onSegment(p1, p2, q1)) return true; 
  
    // p1, q1 and p2 are colinear and q2 lies on segment p1q1 
    if (o2 == 0 && onSegment(p1, q2, q1)) return true; 
  
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2 
    if (o3 == 0 && onSegment(p2, p1, q2)) return true; 
  
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2 
    if (o4 == 0 && onSegment(p2, q1, q2)) return true; 
  
    return false; // Doesn't fall in any of the above cases 
} 
  
// Returns true if the point p lies inside the polygon[] with n vertices 
bool isInside(vector<Point > polygon, int n, Point p) 
{ 
    // There must be at least 3 vertices in polygon[] 
    if (n < 3)  return false; 
  
    // Create a point for line segment from p to infinite 
    Point extreme = {INF, p.y}; 
  
    // Count intersections of the above line with sides of polygon 
    int count = 0, i = 0; 
    do
    { 
        int next = (i+1)%n; 
  
        // Check if the line segment from 'p' to 'extreme' intersects 
        // with the line segment from 'polygon[i]' to 'polygon[next]' 
        if (doIntersect(polygon[i], polygon[next], p, extreme)) 
        { 
            // If the point 'p' is colinear with line segment 'i-next', 
            // then check if it lies on segment. If it lies, return true, 
            // otherwise false 
            if (orientation(polygon[i], p, polygon[next]) == 0) 
               return onSegment(polygon[i], p, polygon[next]); 
  
            count++; 
        } 
        i = next; 
    } while (i != 0); 
  
    // Return true if count is odd, false otherwise 
    return count&1;  // Same as (count%2 == 1) 
} 
  
// Driver program to test above functions 
int main() 
{   
    readFile("output_graham.txt");
    vector<Point > random;
    for(int i = 0; i<10; i++){
        long long int x = rand()%200000;
        long long int y = rand()%200000;
        Point next = {x, y};
        if(isInside(points, points.size(), next)){
            random.push_back(next);
        }
    }
    for (auto i=random.begin(); i!=random.end(); i++){
        cout<<(*i).x<<" "<<(*i).y<<endl;
    }
  
    return 0; 
}