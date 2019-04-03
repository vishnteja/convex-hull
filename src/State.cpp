#include "State.h"

State::State(vector<Point > NP,vector<Point > BP, vector<Point > NE,vector<Point > BE)
{
    normal_points = NP;
    bold_points = BP;
    normal_edges = NE;
    bold_edges = BE;
}

State::State()
{

}

vector<Point > State::getNormalP()
{
    return normal_points;
}

vector<Point > State::getBoldP()
{
    return bold_points;
}

vector<Point > State::getNormalE()
{
    return normal_edges;
}

vector<Point > State::getBoldE()
{
    return bold_edges;
}

