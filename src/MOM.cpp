#include <bits/stdc++.h>
#include "MOM.h"
using namespace std;

void swap(double *a, double *b) 
{ 
    double temp = *a; 
    *a = *b; 
    *b = temp; 
} 

int partition(vector<double> &medArr, int left, int right, double x) 
{ 
    int i; 
    for (i=left; i<right; i++) 
        if (medArr[i] == x) 
           break; 
    swap(&medArr[i], &medArr[right]); 
  
    i = left; 
    for (int j = left; j <= right - 1; j++) 
    { 
        if (medArr[j] <= x) 
        { 
            swap(&medArr[i], &medArr[j]); 
            i++; 
        } 
    } 
    swap(&medArr[i], &medArr[right]); 
    return i; 
} 

double findMedian(vector<double> :: iterator start, vector<double> :: iterator end, int n) 
{ 
    sort(start, end);
    end--;  
    while(start < end)
    {
        start++;
        end--;
    }
    return *end;
} 
  
double kthSmallest(vector<double> &medArr, int left, int right, int k) 
{ 
    
    if (k > 0 && k <= right - left + 1) 
    { 
        int n = right-left+1; 

        int i;
        vector<double> median((n+4)/5);
        for (i=0; i<n/5; i++) 
            median[i] = findMedian(medArr.begin()+left+i*5, medArr.end(), 5); 
        if (i*5 < n) 
        { 
            median[i] = findMedian(medArr.begin()+left+i*5, medArr.end(), n%5);  
            i++; 
        }     
        int medOfMed = (i == 1)? median[i-1]: 
                                 kthSmallest(median, 0, i-1, i/2); 
  
        int pos = partition(medArr, left, right, medOfMed); 
  
        if (pos-left == k-1) 
            return medArr[pos]; 
        if (pos-left > k-1) 
            return kthSmallest(medArr, left, pos-1, k); 
  
        return kthSmallest(medArr, pos+1, right, k-pos+left-1); 
    } 

    return INT_MAX; 
} 

pair<double,int> medOfMed(vector<double> &medArr)
{
    double median = kthSmallest(medArr, 0, medArr.size()-1, 1 + medArr.size()/2); 
    int count = 0;
    // for(int i=0; i<medArr.size(); i++)
    // {
    //     if(medArr[i] == median)
    //         count++;
    // }
    count = 10;
    return pair<double,int>(median, count);
}

pair<double,int> medOfMedPoints(vector<Point > p){
    vector<double > vec;
    for(auto i=p.begin(); i!=p.end(); i++){
        vec.push_back((*i).first);
    }
    return medOfMed(vec);
}
 