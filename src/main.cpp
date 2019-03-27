#include <bits/stdc++.h>
#include "Ultimate.h"

int main(){
    Ultimate chull = Ultimate();
    
    chull.readFile("input_1.txt");
    vector<Point > u = chull.computeUpperHull();
    vector<Point > l = chull.computeLowerHull();

    u.insert(u.end(), l.rbegin(), l.rend());
    
    ofstream out_file;
    out_file.open("output_1.txt");
    for(auto i=u.begin(); i!= u.end(); i++){
        out_file<<(*i).first<<" "<<(*i).second<<endl;
    }
    return 0;
}