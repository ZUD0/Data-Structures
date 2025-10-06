#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

class Solution {
private:
    // Recursive DFS helper
    void dfs(int node, const std::vector<std::vector<int>>& adj, 
             std::vector<bool>& visited, std::stack<int>& st) {
        visited[node] = true;
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, adj, visited, st);
            }
        }
        st.push(node); // push after visiting all neighbors
    }

public:
    // Function to return one possible topological ordering
    std::vector<int> topoSort(int V, const std::vector<std::vector<int>>& adj) {
        std::vector<bool> visited(V, false);
        std::stack<int> st;

        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                dfs(i, adj, visited, st);
            }
        }

        std::vector<int> topoOrder;
        topoOrder.reserve(V);
        while (!st.empty()) {
            topoOrder.push_back(st.top());
            st.pop();
        }

        return topoOrder;
    }
};

int main() {
    // Example 1
    int V = 6;
    std::vector<std::vector<int>> adj(V);
    adj[5].push_back(2);
    adj[5].push_back(0);
    adj[4].push_back(0);
    adj[4].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(1);

    Solution obj;
    std::vector<int> result = obj.topoSort(V, adj);

    std::cout << "Topological Sort (Example 1): ";
    for (int node : result)
        std::cout << node << " ";
    std::cout << "\n";

    // Example 2
    V = 4;
    adj.assign(V, {});
    adj[1].push_back(0);
    adj[2].push_back(0);
    adj[3].push_back(0);

    result = obj.topoSort(V, adj);

    std::cout << "Topological Sort (Example 2): ";
    for (int node : result)
        std::cout << node << " ";
    std::cout << "\n";

    return 0;
}
