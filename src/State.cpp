#include "../include/State.h"

bool operator<(const Point &a, const Point &b){
    if(a.first<b.first){
        return true;
    }else if(a.first == b.first){
        if(a.second < b.second){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

State::State(){
    int id = 1;
    for(auto i=input_points.begin(); i!=input_points.end(); i++){
        Point temp = *i;
        vector<int> temp_val;
        temp_val.push_back(id);
        temp_val.push_back(0);
        temp_val.push_back(0);
        state_table[temp] = temp_val;
        id++; 
    }
}

void State::storeState(vector<Point > points, vector<Segment > edges){
    
    for(auto i=points.begin(); i!=points.end(); i++){
        Point temp = *i;
        vector<int > temp_val = state_table[temp];
        // Set it as bold point
        temp_val[1] = 0;
        temp_val[2] = 1;
        // Update Table
        state_table[temp] = temp_val;
    }

    for(auto i=edges.begin(); i!=edges.end(); i++){
        Segment temp = *i;
        Point a = temp.getP1();
        Point b = temp.getP2();
        vector<int > temp_val_a = state_table[a];
        vector<int > temp_val_b = state_table[b];
        // Update State Column with id
        temp_val_a[1] = temp_val_b[0];
        temp_val_b[1] = temp_val_a[0];
        // Update Bold Flag
        temp_val_a[2] = 1;
        temp_val_b[2] = 1;
        // Update Map with new values;
        state_table[a] = temp_val_a;
        state_table[b] = temp_val_b;
    }
}