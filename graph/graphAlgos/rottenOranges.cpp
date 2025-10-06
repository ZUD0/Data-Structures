#include <iostream>     // cout, cin
#include <vector>       // vector
#include <queue>        // queue
#include <utility>      // pair
// #include <tuple>        // for structured bindings (C++17)

using namespace std;

class Solution {
public:
    // Returns minutes until all oranges rot, or -1 if impossible
    int orangesRotting(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return -1;

        int m = grid.size();
        int n = grid[0].size();
        int freshCnt = 0;
        queue<pair<int,int>> rotten;

        // collect initial rotten oranges and count fresh ones
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 2) {
                    rotten.push({i, j});
                } else if (grid[i][j] == 1) {
                    ++freshCnt;
                }
            }
        }

        if (freshCnt == 0) return 0; // nothing to rot

        vector<pair<int,int>> directions = {{-1,0}, {0,1}, {1,0}, {0,-1}};
        int minutes = 0;

        // BFS level-by-level (each level = 1 minute)
        while (!rotten.empty() && freshCnt > 0) {
            int levelSize = rotten.size();
            for (int i = 0; i < levelSize; ++i) {
                auto [r, c] = rotten.front();
                rotten.pop();

                for (auto [dr, dc] : directions) {
                    int nr = r + dr;
                    int nc = c + dc;
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                        grid[nr][nc] = 2;          // becomes rotten
                        --freshCnt;
                        rotten.push({nr, nc});
                    }
                }
            }
            ++minutes;
        }

        return (freshCnt == 0) ? minutes : -1;
    }
};

int main() {
    int m, n;
    cout << "Enter rows (m) and columns (n): ";
    if (!(cin >> m >> n)) return 0;

    vector<vector<int>> grid(m, vector<int>(n));
    cout << "Enter grid rows (0 empty, 1 fresh, 2 rotten), row by row:\n";
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }

    Solution sol;
    int result = sol.orangesRotting(grid);
    cout << "Result: " << result << "\n";

    return 0;
}
