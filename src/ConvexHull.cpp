#include "ConvexHull.h"
#include <bits/stdc++.h>
#define Point pair<int, int>
using namespace std;

/**
 * @brief This function reads a text file containing the input points.
          Each line should have 1 point seperated by 'space'.
 *  This function stores the resulting vector of pairs in its member input_points
 *  You can retrieve the points by using getInputPoints()
 * @param file_path String containing the path of the input file
 */
void ConvexHull::readFile(string file_path){
    // Note:- Points have to positive integers
    // Read Inputs
    ifstream input_file;
    input_file.open(file_path);

    // Store points in a vector
    vector<Point > points;

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

        // Conver string to int
        int x = stoi(x1);
        int y = stoi(y1);

        points.push_back(make_pair(x, y));
    }

    // Set the input_points member
    this->input_points = points;
}

/**
 * @brief Get function that return the input points.
 * 
 * @return vector<Point > Contains the points as pairs in a vector
 */
vector<Point > ConvexHull::getInputPoints(){
    return this->input_points;
}

