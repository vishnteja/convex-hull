#include "../include/Ultimate.h"
using namespace std;
#define Point pair<int, int>  

/**
 * @brief Prints points
 * Takes vector of points and prints them
 * 
 * @param vec vecttor of pairs
 */
void traverse(vector<Point > vec){
    cout<<endl;
    for (auto i = vec.begin(); i != vec.end(); i++){
        cout << i->first << ", "<<i->second <<endl;
    }
    cout<<endl<<endl;
}

/**
 * @brief Prints Line Segments
 * Takes vector of Line Segments and prints them
 * @param vec vector of segments
 */
void traverse_(vector<Segment > vec){
    cout<<endl;
    for (auto i = vec.begin(); i!= vec.end(); i++){
        cout<< (*i).getP1().first << ", " << (*i).getP1().second << " --- "<< (*i).getP2().first << ", " << (*i).getP2().second<<endl;
    }
    cout<<endl<<endl;
}

/**
 * @brief Construct a default Ultimate object;
 * 
 */
Ultimate::Ultimate(){}

/**
 * @brief Construct a new Ultimate object with input_points initialized
 * Construct a new Ultimate object with input_points initialized.
 * @param file_path input file path
 */
Ultimate::Ultimate(string file_path){
    readFile(file_path);
}

/**
 * @brief computes convex hull stores in output_hull
 * computes convex hull as described in Kirkpatrick-Seidel Algorithm
 */
void Ultimate::computeHull(){
    vector<Point > vec = computeUpperHull();
    vector<Point > low = computeLowerHull();
    vec.insert(vec.end(), low.rbegin(), low.rend());
    output_hull = vec;
}

/**
 * @brief computes upper convex hull
 * 
 * @return vector<Point > vector of points representing the hull
 */
vector<Point > Ultimate::computeUpperHull(){
    // 1. Get Pmin, Pmax (X-Coordinate)
    // Upper - Largest y
    // Lower - Smallest y  
    Point upmin, upmax;
    Point lpmin, lpmax;
    int x_min = 99999, x_max = -1;
    for(auto i=input_points.begin(); i!=input_points.end(); i++){
        Point temp = *i;
        if(temp.first < x_min){
            x_min = temp.first;
            upmin = temp;
            lpmin = temp;
        }else if(temp.first == x_min){
            if(temp.second > upmin.second){
                upmin = temp;
            }
            if(temp.second < lpmin.second){
                lpmin = temp;
            }
        }
        if(temp.first > x_max){
            x_max = temp.first;
            upmax = temp;
            lpmax = temp;
        }else if(temp.first == x_max){
            if(temp.second > upmax.second){
                upmax = temp;
            }
            if(temp.second < lpmax.second){
                lpmax = temp;
            }
        }
    }

    // 2. Upper Hull
    Segment divider = Segment(upmin, upmax);
    
    vector<Point > T;
    T.push_back(upmin);
    for(auto i=input_points.begin(); i!=input_points.end(); i++){
        Point temp = *i;
        if(divider.orientation(temp) < 0)
            T.push_back(temp);
    }
    T.push_back(upmax);

    //Debug
    cout<<"Upper Hull Candidates";
    traverse(T);
    vector<Point > upper_hull = upperHull(upmin, upmax, T);

    return upper_hull;
}

/**
 * @brief computes lower convex hull
 * 
 * @return vector<Point > vector of points representing the hull
 */
vector<Point > Ultimate::computeLowerHull(){
    // 1. Get Pmin, Pmax (X-Coordinate)
    // Upper - Largest y
    // Lower - Smallest y  
    Point upmin, upmax;
    Point lpmin, lpmax;
    int x_min = 99999, x_max = -1;
    for(auto i=input_points.begin(); i!=input_points.end(); i++){
        Point temp = *i;
        if(temp.first < x_min){
            x_min = temp.first;
            upmin = temp;
            lpmin = temp;
        }else if(temp.first == x_min){
            if(temp.second > upmin.second){
                upmin = temp;
            }
            if(temp.second < lpmin.second){
                lpmin = temp;
            }
        }
        if(temp.first > x_max){
            x_max = temp.first;
            upmax = temp;
            lpmax = temp;
        }else if(temp.first == x_max){
            if(temp.second > upmax.second){
                upmax = temp;
            }
            if(temp.second < lpmax.second){
                lpmax = temp;
            }
        }
    }

    // 2. Lower Hull
    Segment divider = Segment(lpmin, lpmax);
    
    vector<Point > T;
    T.push_back(lpmin);
    for(auto i=input_points.begin(); i!=input_points.end(); i++){
        Point temp = *i;
        if(divider.orientation(temp) > 0)
            T.push_back(temp);
    }
    T.push_back(lpmax);


    vector<Point > lower_hull = lowerHull(lpmin, lpmax, T);

    return lower_hull;
}

/**
 * @brief returns the upper hull
 * 
 * @param pmin Leftmost Point
 * @param pmax Rightmost Point
 * @param T Points to consider for the computation
 * @return vector<Point > vector of points representing the hull
 */
vector<Point > Ultimate::upperHull(Point pmin, Point pmax, vector<Point > T){
    if(pmin == pmax){
        // 1. One point Remaining
        vector <Point > singleton;
        singleton.push_back(pmin);
        return singleton;
    }
    else{
        // 2. Find median of the x coordinates
        double median_x = medianX(T);
        median_x = median_x - 0.5;

        // 3. Find Upper Bridge segment pl-pr
        Segment upper_bridge = upperBridge(T, median_x);
        Point pl = upper_bridge.getP1();
        Point pr = upper_bridge.getP2();

        // 4. Discard inner points  & Seperate into T_left and T_right
        vector<Point > Tleft;
        vector<Point > Tright;
        Tleft.push_back(pl);
        if(pl!=pmin){
            Tleft.push_back(pmin);
        }
        Tright.push_back(pr);
        if(pr!=pmax){
            Tright.push_back(pmax);
        }
        for(auto i = T.begin(); i!= T.end(); i++){
            // Note:- Can remove more points
            Point temp = *i;
            if(temp.first < pl.first && temp.first > pmin.first)
                Tleft.push_back((*i));
            else if(temp.first > pr.first && temp.first < pmax.first)
                Tright.push_back((*i));
        }

        //verbose
        cout<<"Pmin:"<<pmin.first<<", "<<pmin.second<<endl;
        cout<<"Pl:"<<pl.first<<", "<<pl.second<<endl;
        cout<<"Tleft: "<<endl;
        traverse(Tleft);

        //verbose
        cout<<"Pr:"<<pr.first<<", "<<pr.second<<endl;
        cout<<"Pmax:"<<pmax.first<<", "<<pmax.second<<endl;
        cout<<"Tright: "<<endl;
        traverse(Tright);

        // 5. Concatenate hull of left and right
        // cout<<"T_Left";
        // traverse(Tleft);
        // cout<<endl;
        vector <Point > left_hull = upperHull(pmin, pl, Tleft);
        // cout<<"T_Right";
        // traverse(Tright);
        // cout<<endl;
        vector <Point > right_hull = upperHull(pr, pmax, Tright);

        // Concatenate 
        vector <Point> res;
        res.push_back(pmin);
        res.insert(res.end(), left_hull.begin(), left_hull.end());
        res.insert(res.end(), right_hull.begin(), right_hull.end());
        res.push_back(pmax);
        // 
        // left_hull.insert( left_hull.end(), right_hull.begin(), right_hull.end());
        return res;
    }
}

/**
 * @brief computes the upper bridge
 * 
 * @param S Points to consider for the computation
 * @param x_median Line x = x_median to consider to split into left and right
 * @return Segment the upper bridge segment
 */
Segment Ultimate::upperBridge(vector<Point > S, double x_median){
    // cout<<"Points Considered for Bridge"<<endl;
    // traverse(S);
    // cout<<endl;
    
    // 1. Array of points which consist of candidates
    vector<Point > candidates;
    
    // 2. if there are only two points remaining they form the bridge
    if(S.size()==2){
        Point pi = S[0];
        Point pj = S[1];
        if(pi.first > pj.first){
            Point temp = pi;
            pi = pj;
            pj = temp;
        }
        Segment bridge = Segment(pi, pj);
        return bridge;
    }

    // 3. Arbitrarily pair up points of S into pairs 
    
    // Random indices
    // Generate position vector
    vector<int> pos(S.size());
    iota(pos.begin(), pos.end(), 0);
    // Random Generator
    random_device random_dev;
    mt19937 generator(random_dev());
    shuffle(pos.begin(), pos.end(), generator);
    
    // Pair points to Segments
    vector<Segment > pairs;
    while(pos.size()>1){
        Point a, b;
        a = S[pos.back()];
        pos.pop_back();
        b = S[pos.back()];
        pos.pop_back();
        pairs.push_back(Segment(a, b));
    }
    // Add the unpaired point to candidates
    if(pos.size() == 1){
        candidates.push_back(S[pos.back()]);
    }

    // 4. Determine Slope Vector
    vector<double> slopes;
    vector<Segment > select_pairs;
    for(auto p = pairs.begin(); p!= pairs.end(); p++){
        Segment select;
        select = *p;

        Point p1 = select.getP1();
        Point p2 = select.getP2();
        if(p1.first == p2.first){
            if(p1.second > p2.second){
                candidates.push_back(p1);
            }else{
                candidates.push_back(p2);
            }
        }else{
            double segment_slope = select.slope();
            select_pairs.push_back(select);
            slopes.push_back(segment_slope);
        }
    }
    //verbose
    cout<<"Select Pairs:"<<endl;
    traverse_(select_pairs);

    // cout<<"After Slope Pruning Candidates:"<<endl;
    // traverse(candidates);
    // cout<<endl;

    // 5. Determine Median slope K
    if (slopes.size()==0){
        cout<<"No Slopes"<<endl;
    }
    // cout<<"Slopes Case: ";
    // for(auto i = slopes.begin(); i!= slopes.end(); i++){
    //     cout<<(*i)<<" ";
    // }
    nth_element(slopes.begin(), slopes.begin()+slopes.size()/2 ,slopes.end());
    double K = slopes[(int)slopes.size()/2];
    // for(auto i = slopes.begin(); i!= slopes.end(); i++){
    //     cout<<(*i)<<" ";
    // }
    // cout<<endl;
    // traverse_(select_pairs);

    // 6. Split points based on slope value
    vector<Segment > small;
    vector<Segment > equal;
    vector<Segment > large;
    while(select_pairs.size()>0){
        Segment select;
        select = select_pairs.back();
        select_pairs.pop_back();
        double segment_slope = select.slope();
        if(segment_slope < K){
            small.push_back(select);
        }else if (segment_slope == K){
            equal.push_back(select);
        }else{
            large.push_back(select);
        }
    }
    // traverse_(small);
    // traverse_(equal);
    // traverse_(large);
    

    // 7. Find a supporting line of S with slope K. Find the points of S that lie on this supporting line
    vector<Point > max;
    double maximum = S[0].second - K*S[0].first;
    Point pk = S[0]; 
    Point pm = S[0];
    max.push_back(S[0]);

    for(auto i = S.begin(); i != S.end(); i++){
        Point p = (*i);
        double y_intercept = p.second - K*p.first;
        if(abs(maximum-y_intercept)<10e-5){
            max.push_back(p);
            if(p.first < pk.first)
                pk = (*i);
            if(p.first > pm.first)
                pm = (*i);
        }else if(y_intercept > maximum){
            maximum = y_intercept;
            max.clear();
            max.push_back(p);
            pk = p;
            pm = p;        
        }
    }
    //verbose
    cout<<"pk: "<<pk.first<<", "<<pk.second<<endl;
    cout<<"pm: "<<pm.first<<", "<<pm.second<<endl<<endl;

    // 8. Determine if h contains the bridge
    if(pk.first <= x_median && pm.first > x_median){
        Segment bridge = Segment(pk, pm);
        return bridge;
    }

    // 9. h contains only points to the left of or on L
    if(pm.first <= x_median){
        Segment temp;
        for(auto i = large.begin(); i!= large.end(); i++){
            temp = *i;
            candidates.push_back(temp.getP2());
        }
        for(auto i = equal.begin(); i!= equal.end(); i++){
            temp = *i;
            candidates.push_back(temp.getP2());
        }
        for(auto i= small.begin(); i!= small.end(); i++){
            temp = *i;
            candidates.push_back(temp.getP1());
            candidates.push_back(temp.getP2());
        }
    }

    // 10. h contains only points of S to the right of L
    if(pk.first > x_median){
        Segment temp;
        for(auto i = small.begin(); i!= small.end(); i++){
            temp = *i;
            candidates.push_back(temp.getP1());
        }
        for(auto i = equal.begin(); i!= equal.end(); i++){
            temp = *i;
            candidates.push_back(temp.getP1());
        }
        for(auto i= large.begin(); i!= large.end(); i++){
            temp = *i;
            candidates.push_back(temp.getP1());
            candidates.push_back(temp.getP2());
        }
    }
    //verbose
    cout<<"Candidates:"<<endl;
    traverse(candidates);

    // 11. return UpperBridge(Candidates, L)
    return upperBridge(candidates, x_median);
}


/**
 * @brief returns the upper hull
 * 
 * @param pmin Leftmost Point
 * @param pmax Rightmost Point
 * @param T Points to consider for the computation
 * @return vector<Point > vector<Point > vector of points representing the hull
 */
vector<Point > Ultimate::lowerHull(Point pmin, Point pmax, vector<Point > T){
    if(pmin == pmax){
        // 1. One point Remaining
        vector <Point > singleton;
        singleton.push_back(pmin);
        return singleton;
    }
    else{
        // 2. Find median of the x coordinates
        double median_x = medianX(T);

        cout<<"Points Considered For Lower Hull"<<endl;
        traverse(T);
        cout<<endl;
        // 3. Find Upper Bridge segment pl-pr
        Segment lower_bridge = lowerBridge(T, median_x);
        Point pl = lower_bridge.getP1();
        Point pr = lower_bridge.getP2();

        // 4. Discard inner points  & Seperate into T_left and T_right
        vector<Point > Tleft;
        vector<Point > Tright;
        Tleft.push_back(pl);
        if(pl!=pmin){
            Tleft.push_back(pmin);
        }
        Tright.push_back(pr);
        if(pr!=pmax){
            Tright.push_back(pmax);
        }
        for(auto i = T.begin(); i!= T.end(); i++){
            // Note:- Can remove more points
            Point temp = *i;
            if(temp.first < pl.first && temp.first > pmin.first)
                Tleft.push_back(temp);
            else if(temp.first > pr.first && temp.first < pmax.first)
                Tright.push_back(temp);
        }


        // 5. Concatenate hull of left and right
        // cout<<"T_Left";
        // traverse(Tleft);
        // cout<<endl;
        vector <Point > left_hull = lowerHull(pmin, pl, Tleft);
        // cout<<"T_Right";
        // traverse(Tright);
        // cout<<endl;
        vector <Point > right_hull = lowerHull(pr, pmax, Tright);

        // Concatenate 
        left_hull.insert( left_hull.end(), right_hull.begin(), right_hull.end());
        return left_hull;
    }
}

/**
 * @brief computes the lower bridge
 * 
 * @param S Points to consider for the computation
 * @param x_median Line x = x_median to consider to split into left and right
 * @return Segment the lower bridge segment
 */
Segment Ultimate::lowerBridge(vector<Point > S, double x_median){
    // cout<<"Points Considered for Bridge"<<endl;
    // traverse(S);
    // cout<<endl;
    
    // 1. Array of points which consist of candidates
    vector<Point > candidates;
    
    // 2. if there are only two points remaining they form the bridge
    if(S.size()==2){
        Point pi = S[0];
        Point pj = S[1];
        if(pi.first > pj.first){
            Point temp = pi;
            pi = pj;
            pj = temp;
        }
        Segment bridge = Segment(pi, pj);
        return bridge;
    }

    // 3. Arbitrarily pair up points of S into pairs 
    
    // Random indices
    // Generate position vector
    vector<int> pos(S.size());
    iota(pos.begin(), pos.end(), 0);
    // Random Generator
    random_device random_dev;
    mt19937 generator(random_dev());
    shuffle(pos.begin(), pos.end(), generator);
    
    // Pair points to Segments
    vector<Segment > pairs;
    while(pos.size()>1){
        Point a, b;
        a = S[pos.back()];
        pos.pop_back();
        b = S[pos.back()];
        pos.pop_back();
        pairs.push_back(Segment(a, b));
    }
    // Add the unpaired point to candidates
    if(pos.size() == 1){
        candidates.push_back(S[pos.back()]);
    }

    // 4. Determine Slope Vector
    vector<double> slopes;
    vector<Segment > select_pairs;
    for(auto p = pairs.begin(); p!= pairs.end(); p++){
        Segment select;
        select = *p;

        Point p1 = select.getP1();
        Point p2 = select.getP2();
        if(p1.first == p2.first){
            // Lower Bridge change > to <
            if(p1.second < p2.second){
                candidates.push_back(p1);
            }else{
                candidates.push_back(p2);
            }
        }else{
            double segment_slope = select.slope();
            select_pairs.push_back(select);
            slopes.push_back(segment_slope);
        }
    }
    // cout<<"After Slope Pruning Candidates:"<<endl;
    // traverse(candidates);
    // cout<<endl;

    // 5. Determine Median slope K
    if (slopes.size()==0){
        cout<<"No Slopes"<<endl;
    }
    // cout<<"Slopes Case: ";
    // for(auto i = slopes.begin(); i!= slopes.end(); i++){
    //     cout<<(*i)<<" ";
    // }
    nth_element(slopes.begin(), slopes.begin()+slopes.size()/2 , slopes.end());
    double K = slopes[(int)slopes.size()/2];
    // for(auto i = slopes.begin(); i!= slopes.end(); i++){
    //     cout<<(*i)<<" ";
    // }
    // cout<<endl;
    // traverse_(select_pairs);

    // 6. Split points based on slope value
    vector<Segment > small;
    vector<Segment > equal;
    vector<Segment > large;
    while(select_pairs.size()>0){
        Segment select;
        select = select_pairs.back();
        select_pairs.pop_back();
        double segment_slope = select.slope();
        if(segment_slope < K){
            small.push_back(select);
        }else if (segment_slope == K){
            equal.push_back(select);
        }else{
            large.push_back(select);
        }
    }
    // traverse_(small);
    // traverse_(equal);
    // traverse_(large);
    

    // 7. Find a supporting line of S with slope K. Find the points of S that lie on this supporting line
    vector<Point > min;
    double minimum = S[0].second - K*S[0].first;
    Point pk = S[0]; 
    Point pm = S[0];
    min.push_back(S[0]);

    for(auto i = S.begin(); i != S.end(); i++){
        Point p = (*i);
        double y_intercept = p.second - K*p.first;
        if(abs(minimum - y_intercept)<10e-5){
            min.push_back(p);
            if(p.first < pk.first)
                pk = p;
            if(p.first > pm.first)
                pm = p;
        }
        else if(y_intercept < minimum){
            minimum = y_intercept;
            min.clear();
            min.push_back(p);
            pk = p;
            pm = p;        
        }
   
    }

    // 8. Determine if h contains the bridge
    if(pk.first <= x_median && pm.first > x_median){
        Segment bridge = Segment(pk, pm);
        return bridge;
    }

    // 9. h contains only points to the left of or on L
    if(pm.first <= x_median){
        Segment temp;
        for(auto i = small.begin(); i!= small.end(); i++){
            temp = *i;
            candidates.push_back(temp.getP2());
        }
        for(auto i = equal.begin(); i!= equal.end(); i++){
            temp = *i;
            candidates.push_back(temp.getP2());
        }
        for(auto i= large.begin(); i!= large.end(); i++){
            temp = *i;
            candidates.push_back(temp.getP1());
            candidates.push_back(temp.getP2());
        }
    }

    // 10. h contains only points of S to the right of L
    if(pk.first > x_median){
        Segment temp;
        for(auto i = large.begin(); i!= large.end(); i++){
            temp = *i;
            candidates.push_back(temp.getP1());
        }
        for(auto i = equal.begin(); i!= equal.end(); i++){
            temp = *i;
            candidates.push_back(temp.getP1());
        }
        for(auto i= small.begin(); i!= small.end(); i++){
            temp = *i;
            candidates.push_back(temp.getP1());
            candidates.push_back(temp.getP2());
        }
    }

    // 11. return UpperBridge(Candidates, L)
    return lowerBridge(candidates, x_median);
}

/**
 * @brief calculates median
 * 
 * @param T points
 * @return double x_median
 */
double Ultimate::medianX(vector<Point > T){
    nth_element(T.begin(), T.begin()+T.size()/2, T.end());
    return T[T.size()/2].first;
}

