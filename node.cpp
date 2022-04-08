#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    string name;
    bool visited;
    int cost;
    Node()
    {
    }
    Node(string n)
    {
        name = n;
        visited = false;
        cost = 0;
    }
};