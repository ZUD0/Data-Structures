#ifndef GRAPH_ADJ_MATRIX_H
#define GRAPH_ADJ_MATRIX_H

#include <iostream>
#include <vector>
#include <queue>

class GraphAdjMatrix {
private:
    int V;
    std::vector<std::vector<int>> matrix;

    void dfsUtil(int v, std::vector<bool>& visited) const {
        visited[v] = true;
        std::cout << v << " ";

        for (int i = 0; i < V; i++) {
            if (matrix[v][i] != 0 && !visited[i]) {
                dfsUtil(i, visited);
            }
        }
    }
    
public:
    // Constructor
    GraphAdjMatrix(int vertices) : V(vertices) {
        matrix.resize(V, std::vector<int>(V, 0));
    }
    
    // Add edge (default weight = 1)
    void addEdge(int src, int dest, int weight = 1, bool directed = false) {
        if (src >= 0 && src < V && dest >= 0 && dest < V) {
            matrix[src][dest] = weight;
            if (!directed) matrix[dest][src] = weight;
        }
    }
    
    // Remove edge
    void removeEdge(int src, int dest, bool directed = false) {
        if (src >= 0 && src < V && dest >= 0 && dest < V) {
            matrix[src][dest] = 0;
            if (!directed) matrix[dest][src] = 0;
        }
    }
    
    // Check if edge exists
    bool hasEdge(int src, int dest) const {
        return (src >= 0 && src < V && dest >= 0 && dest < V && matrix[src][dest] != 0);
    }
    
    // Print adjacency matrix
    void printGraph() const {
        std::cout << "Adjacency Matrix:\n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void bfs(int start) const {
       if (start < 0 || start >= V) return;

        std::vector<bool> visited(V, false);
        std::queue<int> q;

        visited[start] = true;
        q.push(start);

        std::cout << "BFS starting from " << start << ": ";

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            std::cout << u << " ";

            for (int v = 0; v < V; v++) {
                if (matrix[u][v] != 0 && !visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        std::cout << std::endl;
    }

    void dfs(int start) const {
        if (start < 0 || start >= V) return;

        std::vector<bool> visited(V, false);
        std::cout << "DFS starting from " << start << ": ";
        dfsUtil(start, visited);
        std::cout << std::endl;
    }
};



#endif // GRAPH_ADJ_MATRIX_H
