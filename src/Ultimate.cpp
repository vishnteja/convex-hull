#include "Ultimate.h"
using namespace std;
#define Point pair<int, int>  

void traverse(vector<Point > vec){
    cout<<endl;
    for (auto i = vec.begin(); i != vec.end(); i++){
        cout << i->first << ", "<<i->second <<endl;
    }
    cout<<endl;
}

void traverse_(vector<Segment > vec){
    cout<<endl;
    for (auto i = vec.begin(); i!= vec.end(); i++){
        cout<< (*i).getP1().first << ", " << (*i).getP1().second << " --- "<< (*i).getP2().first << ", " << (*i).getP2().second<<endl;
    }
}

Ultimate::Ultimate(){}

Ultimate::Ultimate(string file_path){
    readFile(file_path);
}

void Ultimate::computeHull(){
    // 1. Get Pmin, Pmax (X-Coordinate)
    // Upper - Largest y
    // Lower - Smallest y  
    Point upmin, upmax;
    Point lpmin, lpmax;
    int x_min = 99999, x_max = -1;
    for(auto i=input_points.begin(); i!=input_points.end(); i++){
        if((*i).first < x_min){
            upmin = (*i);
            lpmin = (*i);
        }else if((*i).first == x_min){
            if((*i).second > upmin.second){
                upmin = (*i);
            }
            if((*i).second < lpmin.second){
                lpmin = (*i);
            }
        }
        if((*i).first > x_max){
            upmax = (*i);
            lpmax = (*i);
        }else if((*i).first == x_max){
            if((*i).second > upmax.second){
                upmax = (*i);
            }
            if((*i).second < lpmax.second){
                lpmax = (*i);
            }
        }
    }

    // 2. Upper Hull
    Segment divider = Segment(upmin, upmax);
    
    vector<Point > T;
    T.push_back(upmin);
    for(auto i=input_points.begin(); i!=input_points.end(); i++){
        Point temp = *i;
        int orient = divider.orientation(temp);
        if(orient < 0)
            T.push_back(temp);
    }
    T.push_back(upmax);

    vector<Point > upper_hull = this->upperHull(upmin, upmax, T);

    // 3. Lower Hull
    divider = Segment(lpmin, lpmax);

    T.clear();
    T.push_back(lpmin);
    for(auto i=input_points.begin(); i!=input_points.end(); i++){
        Point temp = *i;
        int orient = divider.orientation(temp);
        if(orient > 0)
            T.push_back(temp);
    }
    T.push_back(lpmax);

    vector<Point > lower_hull = this->lowerHull(lpmax, lpmax, T);

    // 4. Concatenate lower_hull with upper_hull
    lower_hull.insert(lower_hull.end(), upper_hull.begin(), upper_hull.end());
    this->output_hull = lower_hull;
}

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


    vector<Point > upper_hull = upperHull(upmin, upmax, T);

    return upper_hull;
}

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


        // 5. Concatenate hull of left and right
        cout<<"T_Left";
        traverse(Tleft);
        cout<<endl;
        vector <Point > left_hull = upperHull(pmin, pl, Tleft);
        cout<<"T_Right";
        traverse(Tright);
        cout<<endl;
        vector <Point > right_hull = upperHull(pr, pmax, Tright);

        // Concatenate 
        left_hull.insert( left_hull.end(), right_hull.begin(), right_hull.end());
        return left_hull;
    }
}

Segment Ultimate::upperBridge(vector<Point > S, double x_median){
    cout<<"Points Considered for Bridge"<<endl;
    traverse(S);
    cout<<endl;
    
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
    cout<<"After Slope Pruning Candidates:"<<endl;
    traverse(candidates);
    cout<<endl;

    // 5. Determine Median slope K
    if (slopes.size()==0){
        cout<<"No Slopes"<<endl;
    }
    cout<<"Slopes Case: ";
    for(auto i = slopes.begin(); i!= slopes.end(); i++){
        cout<<(*i)<<" ";
    }
    sort(slopes.begin(), slopes.end());
    double K = slopes[(int)slopes.size()/2];
    for(auto i = slopes.begin(); i!= slopes.end(); i++){
        cout<<(*i)<<" ";
    }
    cout<<endl;
    traverse_(select_pairs);

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
    traverse_(small);
    traverse_(equal);
    traverse_(large);
    

    // 7. Find a supporting line of S with slope K. Find the points of S that lie on this supporting line
    vector<Point > max;
    double maximum = S[0].second - K*S[0].first;
    Point pk = S[0]; 
    Point pm = S[0];
    max.push_back(S[0]);

    for(auto i = S.begin(); i != S.end(); i++){
        Point p = (*i);
        double y_intercept = p.second - K*p.first;
        if(y_intercept > maximum){
            maximum = y_intercept;
            max.clear();
            max.push_back(p);
            pk = p;
            pm = p;        
        }
        else if(y_intercept == maximum){
            max.push_back(p);
            if(p.first < pk.first)
                pk = (*i);
            if(p.first > pm.first)
                pm = (*i);
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

    // 11. return UpperBridge(Candidates, L)
    return upperBridge(candidates, x_median);
}

bool compare(Point p1, Point p2){
    if(p1.first<p2.first)
        return true;
    else if(p1.first==p2.first)
        return p1.second<p2.second;
    else
        return false;
    
}

double Ultimate::medianX(vector<Point > T){
    sort(T.begin(), T.end(), compare);
    int N = T.size();
    int med = (int)N/2;
    Point a = T[med];
    double median_x = a.first;
    
    // Find spliting x
    
    // Reduce median
    double med_update = a.first - 0.5;
    int less = 0;
    int more = 0;
    for(auto i = T.begin(); i!= T.end(); i++){
        if((*i).first < med_update){
            less++;
        }
        else if((*i).first > med_update){
            more++;
        }
    }
    if(less==more || abs(less-more)==1){
        median_x = med_update;
    }

    // Increase median
    med_update = a.first + 0.5;
    less = 0;
    more = 0;
    for(auto i = T.begin(); i!= T.end(); i++){
        if((*i).first < med_update){
            less++;
        }
        else if((*i).first > med_update){
            more++;
        }
    }
    if(less==more || abs(less-more)==1){
        median_x = med_update;
    }

    return median_x;
}

vector<Point > Ultimate::lowerHull(Point pmin, Point pmax, vector<Point > T){
    if(pmin == pmax){
        // 1. One point Remaining
        vector <Point > singleton;
        singleton.push_back(pmin);
        return singleton;
    }
    else{
        // 2. Find median of the x coordinates
        float median_x = medianX(T);

        // 3. Find Upper Bridge segment pl-pr
        Segment upper_bridge = lowerBridge(T, median_x);
        Point pl = upper_bridge.getP1();
        Point pr = upper_bridge.getP2();

        // 4. Discard inner points  & Seperate into T_left and T_right
        vector <Point > Tleft;
        vector <Point > Tright;
        Tleft.push_back(pl);
        Tright.push_back(pr);
        for(auto i = T.begin(); i!= T.end(); i++){
            // Note:- Can remove more points
            if(i->first < pl.first)
                Tleft.push_back((*i));
            else if(i->first > pr.first)
                Tright.push_back((*i));
        }

        // 5. Concatenate hull of left and right
        vector <Point > left_hull = upperHull(pmin, pl, Tleft);
        vector <Point > right_hull = upperHull(pr, pmax, Tright);

        // Concatenate 
        left_hull.insert( left_hull.end(), right_hull.begin(), right_hull.end());
        return left_hull;
    }
}

Segment Ultimate::lowerBridge(vector<Point > S, double x_median){
    // 1. Array of points which consist of candidates
    vector<Point > candidates;
    
    // 2. if there are only two points remaining they form the bridge
    if(S.size()==2){
        Segment bridge = Segment(S[0], S[1]);
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
    vector<float> slopes;
    for(auto p = pairs.begin(); p!= pairs.end(); p++){
        Segment select;
        select = *p;

        Point p1 = select.getP1();
        Point p2 = select.getP2();
        if(p1.first == p2.first){
            if(p1.second < p2.second){
                candidates.push_back(p1);
            }else{
                candidates.push_back(p2);
            }
        }else{
            slopes.push_back(select.slope());
        }
    }

    // 5. Determine Median slope K
    sort(slopes.begin(), slopes.end());
    float K = slopes[(int)slopes.size()/2];

    // 6. Split points based on slope value
    vector<Segment > small;
    vector<Segment > equal;
    vector<Segment > large;
    while(pairs.size()>0){
        Segment select;
        select = pairs.back();
        pairs.pop_back();
        if(select.slope()< K){
            small.push_back(select);
        }else if (select.slope() == K){
            equal.push_back(select);
        }else{
            large.push_back(select);
        }
    }

    // 7. Find a supporting line of S with slope K. Find the points of S that lie on this supporting line
    vector<Point > min;
    float minimum = S[0].second - K*S[0].first;
    Point pk = S[0]; 
    Point pm = S[0];
    min.push_back(S[0]);

    for(auto i = S.begin(); i != S.end(); i++){
        float y_intercept = (*i).second - K*(*i).first;
        if(y_intercept < minimum){
            minimum = y_intercept;
            min.clear();
            min.push_back((*i));
            pk = (*i);
            pm = (*i);        
        }
        else if(y_intercept == minimum){
            min.push_back((*i));
            if((*i).first < pk.first)
                pk = (*i);
            if((*i).first > pm.first)
                pm = (*i);
        }
    }

    // 8. Determine if h contains the bridge
    if(pk.first <= x_median && pm.first > x_median){
        Segment bridge = Segment(pk, pm);
        return bridge;
    }

    // 9. h contains only points to the left of or on L
    if(pm.first <= x_median){
        for(auto i = large.begin(); i!= large.end(); i++){
            candidates.push_back((*i).getP2());
        }
        for(auto i = equal.begin(); i!= equal.end(); i++){
            candidates.push_back((*i).getP2());
        }
        for(auto i= small.begin(); i!= small.end(); i++){
            candidates.push_back((*i).getP1());
            candidates.push_back((*i).getP2());
        }
    }

    // 10. h contains only points of S to the right of L
    if(pk.first > x_median){
        for(auto i = small.begin(); i!= small.end(); i++){
            candidates.push_back((*i).getP1());
        }
        for(auto i = equal.begin(); i!= equal.end(); i++){
            candidates.push_back((*i).getP1());
        }
        for(auto i= large.begin(); i!= large.end(); i++){
            candidates.push_back((*i).getP1());
            candidates.push_back((*i).getP2());
        }
    }

    // 11. return UpperBridge(Candidates, L)
    return upperBridge(candidates, x_median);
}