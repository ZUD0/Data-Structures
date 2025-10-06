#include <iostream>
#include <vector>
#include <queue>

class Solution {
public:
    std::vector<int> topoSort(int V, const std::vector<std::vector<int>>& adj) {
        std::vector<int> indegree(V, 0);
        
        // Step 1: Compute indegree of each vertex
        for (int u = 0; u < V; ++u) {
            for (int v : adj[u]) {
                indegree[v]++;
            }
        }

        std::queue<int> q;
        // Step 2: Push all vertices with indegree 0
        for (int i = 0; i < V; ++i) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        std::vector<int> topoOrder;
        topoOrder.reserve(V);

        // Step 3: Process the queue
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            topoOrder.push_back(node);

            // Decrease indegree of adjacent nodes
            for (int neighbor : adj[node]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        return topoOrder;
    }
};
