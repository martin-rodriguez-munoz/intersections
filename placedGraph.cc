#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include "placedGraph.h"
using namespace std;

//C = 1/3
placedGraph::placedGraph(const string& filename)
{
    try
    {
        ifstream inFile;
        inFile.open(filename);
        if (inFile.fail()) 
        {
            error = "File not found";
            return;
        }
        int n;
        inFile >> n;
        cout << "n = " << n << endl;
        nodes = vector<Node>(n);
        for (int i = 0; i < n; ++i) inFile >> nodes[i].x >> nodes[i].y;
        int a, b;
        while(inFile >> a >> b)
        {
           Edge inputedge;
           inputedge.u = a;
           inputedge.v = b;
           edges.push_back(inputedge);
        }
    }
    catch(string s)
    {
        error = s;
    }
}

//Takes in a vector of edges returns the number of intersections of those edges
int placedGraph::bruteforce(const vector<Edge> &alledges) const
{
    return 0;
}

int placedGraph::calcNumCrossing(const vector<Edge> &alledges, double line, double step)
{
    if (alledges.size() <= 50)
    {
        return bruteforce(alledges);
    }
    
    vector<Edge> left;
    vector<Edge> center;
    vector<Edge> right;
    for (Edge e : alledges)
    {
        if (nodes[e.u].x <= line and nodes[e.v].x <= line)
        {
            left.push_back(e);
        }
        else if (nodes[e.u].x > line and nodes[e.v].x > line)
        {
            right.push_back(e);
        }
        else
        {
            left.push_back(e);
            right.push_back(e);
            center.push_back(e);
        }
    }
    if (double(center.size())/double(left.size()+right.size()-center.size()) < 1.0/3.0)
    {
        return (calcNumCrossing(left,line-step,step/2)+calcNumCrossing(right,line+step,step/2)+bruteforce(center));
    }
    return bruteforce(alledges);
}

int placedGraph::numCrossings() const
{
    return 1;
}

const string& placedGraph::getError() const
{
    return error;
}
