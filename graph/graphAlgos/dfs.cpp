#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Graph {
private:
    int V;                        // number of vertices
    vector<vector<int>> adj;      // adjacency list
    vector<int> visited;          // visited array

public:
    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
        visited.assign(V, 0);
    }

    void addEdge(int u, int v, bool isDirected = false) {
        adj[u].push_back(v);
        if (!isDirected)
            adj[v].push_back(u);
    }

    // ---------- Recursive DFS ----------
    void dfsRecursive(int node) {
        visited[node] = 1;
        cout << node << " ";

        for (int neighbor : adj[node]) {
            if (!visited[neighbor])
                dfsRecursive(neighbor);
        }
    }

    void dfsRecursiveStart(int start) {
        fill(visited.begin(), visited.end(), 0);
        cout << "Recursive DFS starting from " << start << ": ";
        dfsRecursive(start);
        cout << endl;
    }

    // ---------- Iterative DFS ----------
    void dfsIterative(int start) {
        vector<int> vis(V, 0);
        stack<int> st;
        st.push(start);

        cout << "Iterative DFS starting from " << start << ": ";

        while (!st.empty()) {
            int node = st.top();
            st.pop();

            if (!vis[node]) {
                vis[node] = 1;
                cout << node << " ";
            }

            // reverse order for consistent traversal with recursion
            for (auto it = adj[node].rbegin(); it != adj[node].rend(); ++it) {
                if (!vis[*it])
                    st.push(*it);
            }
        }
        cout << endl;
    }

    // ---------- DFS for Disconnected Graph ----------
    void dfsDisconnected() {
        fill(visited.begin(), visited.end(), 0);
        cout << "DFS for disconnected graph: ";
        for (int i = 0; i < V; ++i) {
            if (!visited[i])
                dfsRecursive(i);
        }
        cout << endl;
    }

    // Optional: print adjacency list
    void printGraph() {
        cout << "\nAdjacency List:\n";
        for (int i = 0; i < V; ++i) {
            cout << i << " -> ";
            for (int nbr : adj[i]) cout << nbr << " ";
            cout << "\n";
        }
    }
};

int main() {
    Graph g(6);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);

    g.printGraph();
    cout << endl;

    g.dfsRecursiveStart(0);
    g.dfsIterative(0);
    g.dfsDisconnected();

    return 0;
}
