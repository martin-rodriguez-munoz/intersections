#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include "placedGraph.h"
using namespace std;

double C = 1.0/3.0;
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

//Given a segment and 2 points checks if the points are on the same side of the segment
bool placedGraph::sameSide(Edge e, Node a, Node b) const
{
    const Node p = nodes[e.u];
    const Node q = nodes[e.v];
    double dx = p.x-q.x;
    double dy = p.y-q.y;
    double dxA = a.x-p.x;
    double dyA = a.y-p.y;
    double dxB = b.x-p.x;
    double dyB = b.y-p.y;
    return (dy*dxA-dx*dyA > 0) == (dy*dxB-dx*dyB > 0);
}

//Given 2 edges checks if they share a node
bool placedGraph::shareNode(Edge a, Edge b) const
{
    return (a.u == b.u) or (a.u == b.v) or (a.v == b.u) or (a.v == b.v);
}

//Given 2 edges checks if they intersect
bool placedGraph::intersect(Edge a, Edge b) const
{
    if (shareNode(a,b)) return false;
    return not (sameSide(a,nodes[b.u],nodes[b.v]) or sameSide(b,nodes[a.u],nodes[a.v]));
    
}

//Takes in a vector of edges returns the number of intersections of those edges
int placedGraph::bruteforce(const vector<Edge> &alledges) const
{
    int ans = 0;
    for (unsigned int i = 0; i < alledges.size(); ++i)
    {
        for (unsigned int j = 0; j < i; ++j)
        {
            if (intersect(alledges[i],alledges[j]))
            {
                ++ans;
            } 
        }
    }
    return ans;
}

int placedGraph::calcNumCrossing(const vector<Edge> &alledges, double line, double step) const
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
        
    if (double(center.size())/double(left.size()+right.size()-center.size()) < C)
    {
        int toreturn = calcNumCrossing(left,line-step,step/2);
        toreturn += calcNumCrossing(right,line+step,step/2);
        toreturn -= bruteforce(center);
        return toreturn;
    }
    return bruteforce(alledges);
}

int placedGraph::numCrossings() const
{
    return calcNumCrossing(edges,0,0.5);
}

const string& placedGraph::getError() const
{
    return error;
}
