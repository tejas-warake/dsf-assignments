#include <iostream>
#include <list>
using namespace std;

class Graph
{
    int n;
    list<int> *adjLists;
    bool *visited;

public:
    Graph(int V);
    void addEdge(int src, int dest);
    void DFS(int vertex);
    void BFS(int startVertex);
};

// Initialize graph
Graph::Graph(int vertices)
{
    n = vertices;
    adjLists = new list<int>[vertices];
    visited = new bool[vertices];
}

// Adding new edge
void Graph::addEdge(int src, int dest)
{
    adjLists[src].push_front(dest);
}

// Depth First Search Algorithm
void Graph::DFS(int vertex)
{
    visited[vertex] = true;
    list<int> adjList = adjLists[vertex];

    cout << vertex << " ";

    list<int>::iterator i;
    for (i = adjList.begin(); i != adjList.end(); ++i)
        if (!visited[*i])
            DFS(*i);
}

// Breadth First Search Algorithm
void Graph::BFS(int startVertex)
{
    visited = new bool[n];
    for (int i = 0; i < n; i++)
        visited[i] = false;

    list<int> queue;

    visited[startVertex] = true;
    queue.push_back(startVertex);

    list<int>::iterator i;

    while (!queue.empty())
    {
        int currVertex = queue.front();
        cout << "Visited " << currVertex << " ";
        queue.pop_front();

        for (i = adjLists[currVertex].begin(); i != adjLists[currVertex].end(); ++i)
        {
            int adjVertex = *i;
            if (!visited[adjVertex])
            {
                visited[adjVertex] = true;
                queue.push_back(adjVertex);
            }
        }
    }
}

int main()
{
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(3, 2);
    g.addEdge(2, 3);
    g.addEdge(1, 0);
    g.addEdge(2, 1);
    g.addEdge(2, 4);
    g.addEdge(4, 2);
    g.addEdge(3, 4);
    g.addEdge(4, 3);

    cout<<"Depth First Search Traversal: \n";
    g.DFS(2);cout<<endl;
    cout<<"Breadth First Search Traversal: \n";
    g.BFS(2);
    return 0;
}