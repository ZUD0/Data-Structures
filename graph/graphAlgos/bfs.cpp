#include <iostream>
#include <vector>
#include <queue>
#include <algorithm> // for fill

using namespace std;

class Graph {
private:
    int V;                            // number of vertices
    vector<vector<int>> adj;          // adjacency list

public:
    // Constructor
    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
    }

    // Add edge to graph (default: undirected)
    void addEdge(int u, int v, bool isDirected = false) {
        adj[u].push_back(v);
        if (!isDirected)
            adj[v].push_back(u);
    }

    // Print adjacency list
    void printGraph() const {
        cout << "\nAdjacency List:\n";
        for (int i = 0; i < V; ++i) {
            cout << i << " -> ";
            for (int nbr : adj[i])
                cout << nbr << " ";
            cout << "\n";
        }
    }

    // Perform BFS from a starting node
    void bfs(int start) const {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS traversal starting from node " << start << ": ";

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    // BFS for disconnected graph
    void bfsDisconnected() const {
        vector<bool> visited(V, false);
        cout << "BFS for disconnected graph: ";

        for (int start = 0; start < V; ++start) {
            if (!visited[start]) {
                queue<int> q;
                visited[start] = true;
                q.push(start);

                while (!q.empty()) {
                    int node = q.front();
                    q.pop();
                    cout << node << " ";

                    for (int neighbor : adj[node]) {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }
            }
        }
        cout << endl;
    }
};

int main() {
    int vertices, edges;
    cout << "Enter number of vertices: ";
    cin >> vertices;

    Graph g(vertices);

    cout << "Enter number of edges: ";
    cin >> edges;

    cout << "Enter edges (u v):" << endl;
    for (int i = 0; i < edges; ++i) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v); // undirected by default
    }

    g.printGraph();
    cout << endl;

    int start;
    cout << "Enter starting node: ";
    cin >> start;

    g.bfs(start);
    g.bfsDisconnected(); // optional

    return 0;
}
