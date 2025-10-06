#include <iostream>
#include <vector>
using namespace std;

class Graph {
private:
    vector<vector<int>> isConnected;  // adjacency matrix
    vector<int> visited;
    int n;  // number of cities

    // Depth-First Search helper
    void dfs(int i) {
        visited[i] = 1;
        for (int j = 0; j < n; ++j) {
            if (isConnected[i][j] == 1 && !visited[j]) {
                dfs(j);
            }
        }
    }

public:
    // Constructor
    Graph(const vector<vector<int>>& matrix) {
        isConnected = matrix;
        n = isConnected.size();
        visited.assign(n, 0);
    }

    // Count number of connected components (provinces)
    int countProvinces() {
        int count = 0;
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                dfs(i);
                count++;
            }
        }
        return count;
    }
};

int main() {
    int n;
    cout << "Enter number of cities: ";
    cin >> n;

    vector<vector<int>> matrix(n, vector<int>(n));
    cout << "Enter adjacency matrix (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }

    Graph g(matrix);
    cout << "Number of Provinces: " << g.countProvinces() << endl;

    return 0;
}
