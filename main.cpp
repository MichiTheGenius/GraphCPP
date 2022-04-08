#include "graph.cpp"
#include <iostream>
#include <string>
using namespace std;
int main()
{
    Graph g;
    g.addNode("Schwandorf");
    g.addNode("Regensburg");
    g.addNode("Berlin");
    g.addNode("Haselbach");
    g.addNode("Valhalla");
    g.addNode("Muenchen");
    g.addNode("Nuernberg");
    g.addNode("Wackersdorf");
    g.addNode("Paris");
    g.addNode("NewYork");
    g.fillMatrix();
    g.addEdge("Schwandorf", "Regensburg", 40);
    g.addEdge("Valhalla", "Nuernberg", 239);
    g.addEdge("Haselbach", "Valhalla", 69000);
    g.addEdge("Regensburg", "Haselbach", 35);
    g.addEdge("Valhalla", "NewYork", 35929);
    g.addEdge("NewYork", "Wackersdorf", 420);
    g.addEdge("Wackersdorf", "Paris", 42032);
    g.printMatrix();
    // g.DFSKickoff("Schwandorf");
    g.Dijkstra("Schwandorf", "Nuernberg");
    g.printCost();

    return 0;
}