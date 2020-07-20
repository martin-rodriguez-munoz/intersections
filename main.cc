#include <string>
#include <iostream>
#include "placedGraph.h"
using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " infile" << endl;
    return 1;
  }

  placedGraph G(argv[1]);

  const string &err = G.getError();
  if (not err.empty()) {
    cerr << "Error: " << err << endl;
    return 1;
  }

  cout << "Number of crossings: " << G.numCrossings() << endl;
  return 0;
}
