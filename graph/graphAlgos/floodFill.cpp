#include <iostream>   // cin, cout
#include <vector>     // vector
#include <queue>      // queue
#include <utility>    // pair

using namespace std;

class FloodFiller {
public:
    // Perform flood fill (BFS). Modifies and returns the image.
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        if (image.empty() || image[0].empty()) return image;

        int m = image.size();
        int n = image[0].size();
        int oldColor = image[sr][sc];
        if (oldColor == color) return image; // nothing to do

        queue<pair<int,int>> q;
        q.push(make_pair(sr, sc));
        image[sr][sc] = color;

        const vector<pair<int,int>> directions = {
            make_pair(-1, 0),
            make_pair(0, 1),
            make_pair(1, 0),
            make_pair(0, -1)
        };

        while (!q.empty()) {
            pair<int,int> top = q.front();
            q.pop();

            for (size_t d = 0; d < directions.size(); ++d) {
                int r = top.first + directions[d].first;
                int c = top.second + directions[d].second;

                if (r >= 0 && r < m && c >= 0 && c < n && image[r][c] == oldColor) {
                    image[r][c] = color;
                    q.push(make_pair(r, c));
                }
            }
        }

        return image;
    }
};

int main() {
    int m, n;
    // Input format:
    // m n
    // m rows each with n integers (the image)
    // sr sc color
    if (!(cin >> m >> n)) return 0;

    vector<vector<int>> image(m, vector<int>(n));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> image[i][j];

    int sr, sc, color;
    cin >> sr >> sc >> color;

    FloodFiller ff;
    vector<vector<int>> result = ff.floodFill(image, sr, sc, color);

    // Print the resulting image
    for (int i = 0; i < (int)result.size(); ++i) {
        for (int j = 0; j < (int)result[i].size(); ++j) {
            cout << result[i][j];
            if (j + 1 < (int)result[i].size()) cout << " ";
        }
        cout << "\n";
    }

    return 0;
}
