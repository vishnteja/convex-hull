#include <bits/stdc++.h>
#include "include/ConvexHull.h"

int main(int argc, char*argv[]){
    
    string input_string = string(argv[1]);
    string algo_name = string(argv[2]);
    cout<<"Argument "<<input_string<<endl;
    cout<<"Argument "<<algo_name<<endl;
    
    ConvexHull chull = ConvexHull();

    chull.readFile(string(argv[1]));
    vector<Point > vec = chull.getInputPoints();
    // for(auto i=vec.begin(); i!= vec.end(); i++){
    //     cout<<(*i).first<<" "<<(*i).second<<endl;
    // }
    
    chull.computeHull(algo_name);
    vec = chull.getOutput();
    
    ofstream out_file;
    
    out_file.open("output_"+algo_name+".txt");
    for(auto i=vec.begin(); i!= vec.end(); i++){
        out_file<<(*i).first<<" "<<(*i).second<<endl;
    }

    
    // vector<Point > p;
    // p.push_back(make_pair(0, 1));
    // p.push_back(make_pair(1, 9));
    // p.push_back(make_pair(1, 4));
    // p.push_back(make_pair(1, 8));
    // p.push_back(make_pair(1, 17));
    // p.push_back(make_pair(1, 3));
    // p.push_back(make_pair(5,19));
    // p.push_back(make_pair(5, 3));
    
    // nth_element(p.begin(), p.begin()+p.size()/2, p.end(), compare);
    // for(auto i=p.begin(); i!= p.end(); i++){
    //     cout<<(*i).first<<" "<<(*i).second<<endl;
    // }
    // cout<<endl<<p[p.size()/2].first<<" "<<p[p.size()/2].second<<endl;
    // sort(p.begin(), p.end(), compare);
    // for(auto i=p.begin(); i!=p.end(); i++){
    //     cout<<(*i).first<<" "<<(*i).second<<endl;
    // }
    // cout<<endl<<p[p.size()/2].first<<" "<<p[p.size()/2].second<<endl;
    
   
    return 0;
}