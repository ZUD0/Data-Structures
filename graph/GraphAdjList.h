#ifndef GRAPH_ADJ_LIST_H
#define GRAPH_ADJ_LIST_H

#include <iostream>
#include <vector>
#include <list>
#include <queue>

class GraphAdjList {
private:
    int V;
    std::vector<std::list<int>> adjList;

    void dfsUtil(int v, std::vector<bool>& visited) const {
        visited[v] = true;
        std::cout << v << " ";

        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                dfsUtil(neighbor, visited);
            }
        }
    }

public:
    // Constructor
    GraphAdjList(int vertices) : V(vertices) {
        adjList.resize(V);
    }

    // Add edge
    void addEdge(int src, int dest, bool directed = false) {
        if (src >= 0 && src < V && dest >= 0 && dest < V) {
            adjList[src].push_back(dest);
            if (!directed) adjList[dest].push_back(src);
        }
    }

    // Remove edge
    void removeEdge(int src, int dest, bool directed = false) {
        if (src >= 0 && src < V && dest >= 0 && dest < V) {
            adjList[src].remove(dest);
            if (!directed) adjList[dest].remove(src);
        }
    }

    // Check if edge exists
    bool hasEdge(int src, int dest) const {
        if (src < 0 || src >= V || dest < 0 || dest >= V) return false;
        for (int neighbor : adjList[src]) {
            if (neighbor == dest) return true;
        }
        return false;
    }

    // Print adjacency list
    void printGraph() const {
        std::cout << "Adjacency List:\n";
        for (int i = 0; i < V; i++) {
            std::cout << i << ": ";
            for (int neighbor : adjList[i]) {
                std::cout << neighbor << " ";
            }
            std::cout << std::endl;
        }
    }

    // BFS
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

            for (int neighbor : adjList[u]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        std::cout << std::endl;
    }

    // DFS
    void dfs(int start) const {
        if (start < 0 || start >= V) return;

        std::vector<bool> visited(V, false);
        std::cout << "DFS starting from " << start << ": ";
        dfsUtil(start, visited);
        std::cout << std::endl;
    }
};

#endif // GRAPH_ADJ_LIST_H
