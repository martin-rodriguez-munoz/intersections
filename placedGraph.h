#include <vector>

class placedGraph{

public:
    /// Reads a placed graph from a file. The graph has the following format
    /// n -> Number of nodes, numbered from 0 to n-1
    /// x0 y0 x1 y1 ... x(n-1) y(n-1) -> coordinates of the nodes (real numbers)
    /// n1 n2 n3 n4 -> pairs of nodes representing the edges.
    /// If an error is produced (e.g., file not found or wrong format)
    placedGraph(const std::string& filename);

    /// Returns the error associated to the graph (empty string if no error)
    const std::string& getError() const;

    /// Returns the number of crossings between edges of the graph
    int numCrossings() const;

private:    
    // Node of the graph
    struct Node {
        double x, y;        // Coordinates of the nodes
    };

    // Edge of the graph
    struct Edge {
        int u, v;           // Indices of the node. Enforce u <= v.
        double distance;    // Distance between the two nodes (we may need it).
    };

    std::vector<Node> nodes;     // List of nodes
    std::vector<Edge> edges;     // List of edges
    std::string error;           // Error message
    
    int bruteforce(const std::vector<Edge> &alledges) const;
    int calcNumCrossing(const std::vector<Edge> &alledges, double line, double step);
};
