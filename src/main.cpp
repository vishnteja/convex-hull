#include <bits/stdc++.h>
#include "Ultimate.h"
#include "Jarvis.h"

int main(){
    Jarvis chull = Jarvis();
    
    chull.readFile("input_1.txt");
    chull.computeHull();
    vector<Point > vec = chull.getOutput();
    
    ofstream out_file;
    out_file.open("output_1.txt");
    for(auto i=vec.begin(); i!= vec.end(); i++){
        out_file<<(*i).first<<" "<<(*i).second<<endl;
    }
    return 0;
}