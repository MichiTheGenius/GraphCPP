#include "node.cpp"
#include <iostream>
#include <string>
#include <climits>
using namespace std;

class Graph
{
private:
    const int columnLength = 13;
    const int rowLength = 12;
    static constexpr int amountOfNodes = 10;
    int nodeCounter = 0;
    int matrix[amountOfNodes][amountOfNodes];
    Node nodes[amountOfNodes];

public:
    Graph()
    {
    }
    void addNode(string n)
    {
        if (nodeCounter < amountOfNodes)
        {
            Node newNode = Node(n);
            nodes[nodeCounter] = newNode;
            nodeCounter++;
        }
    }

    void fillMatrix()
    {
        for (int i = 0; i < amountOfNodes; i++)
        {
            for (int j = 0; j < amountOfNodes; j++)
            {
                matrix[i][j] = -1;
            }
            matrix[i][i] = 0;
        }
    }

    void printMatrix()
    {
        for (int i = 0; i < rowLength; i++)
        {
            cout << " ";
        }
        for (int i = 0; i < amountOfNodes; i++)
        {
            string currentNode = nodes[i].name;
            cout << fixedLength(currentNode, columnLength);
        }
        cout << "\n";
        for (int i = 0; i < amountOfNodes; i++)
        {
            string currentNode = nodes[i].name;
            cout << fixedLength(currentNode, rowLength) << "|";
            for (int j = 0; j < amountOfNodes; j++)
            {
                string currentCell = to_string(matrix[i][j]);
                cout << fixedLength(currentCell, columnLength);
            }
            cout << "\n";
        }
    }

    int getNodeIndex(string n)
    {
        for (int i = 0; i < amountOfNodes; i++)
        {
            if (nodes[i].name == n)
            {
                return i;
            }
        }
        return -1;
    }

    void addEdge(string node1, string node2, int value)
    {
        int index1 = getNodeIndex(node1);
        int index2 = getNodeIndex(node2);
        if (index1 == -1 || index2 == -1)
        {
            return;
        }

        matrix[index1][index2] = value;
        matrix[index2][index1] = value;
    }

    string fixedLength(string s, int len)
    {
        if (s.length() > len)
        {
            s = s.substr(0, len);
        }
        else if (s.length() < len)
        {
            string spaces = "";
            for (int i = 0; i < len; i++)
            {
                spaces += " ";
            }
            s = (s + spaces).substr(0, len);
        }
        return s;
    }

    void DFSKickoff(string start)
    {
        int startingNode = getNodeIndex(start);
        if (startingNode == -1)
            return;
        DFS(startingNode);
    }

    void DFS(int currentNode)
    {
        nodes[currentNode].visited = true;
        cout << "Visited: " << nodes[currentNode].name << "; ";

        for (int i = 0; i < amountOfNodes; i++)
        {
            if (matrix[currentNode][i] > 0 && !nodes[i].visited)
            {
                DFS(i);
                cout << "Back to: " << nodes[currentNode].name + "; ";
            }
        }
        cout << "Finished with: " << nodes[currentNode].name << "\n";
    }

    int getNodeWithSmallestCost()
    {
        int smallest = INT32_MAX;
        int indexOfSmallest = 0;
        for (int i = 0; i < amountOfNodes; i++)
        {
            int currentCost = nodes[i].cost;
            if (currentCost < smallest && !nodes[i].visited)
            {
                smallest = currentCost;
                indexOfSmallest = i;
            }
        }
        return indexOfSmallest;
    }

    void printCost()
    {
        for (int i = 0; i < amountOfNodes; i++)
        {
            cout << nodes[i].name << ": " << nodes[i].cost << "\n";
        }
    }

    void Dijkstra(string start, string target)
    {
        int startingNode = getNodeIndex(start);
        int targetNode = getNodeIndex(target);
        if (startingNode == -1 || targetNode == -1)
        {
            cout << "CRITICAL ERROR!" << endl;
            return;
        }
        for (int i = 0; i < amountOfNodes; i++)
        {
            nodes[i].cost = INT32_MAX;
        }
        nodes[startingNode].cost = 0;

        int selectedNode;
        for (int i = 0; i < amountOfNodes; i++)
        {
            // get the node with the smallest cost at the start
            selectedNode = getNodeWithSmallestCost();
            nodes[selectedNode].visited = true;
            for (int j = 0; j < amountOfNodes; j++)
            {
                // go through all of the neighbor nodes
                // they have to be unvisited and have an edge to them
                if (!nodes[j].visited && matrix[selectedNode][j] > 0)
                {
                    // the new cost is the cost from the current selected node + the path to the new
                    // neighbor node
                    int newCost = nodes[selectedNode].cost + matrix[selectedNode][j];
                    if (newCost < nodes[j].cost)
                    {
                        nodes[j].cost = newCost;
                    }
                }
            }
        }

        cout << "The shortest path from " << start << " to " << target << " is: " << nodes[targetNode].cost << endl;
    }
};
