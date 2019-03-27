#include <bits/stdc++.h>
#include "Ultimate.h"

int main(){
    Ultimate chull = Ultimate();
    
    chull.readFile("input_1.txt");
    vector<Point > v = chull.computeUpperHull();
    
    ofstream out_file;
    out_file.open("output_1.txt");
    for(auto i=v.begin(); i!= v.end(); i++){
        out_file<<(*i).first<<" "<<(*i).second<<endl;
    }
    return 0;
}