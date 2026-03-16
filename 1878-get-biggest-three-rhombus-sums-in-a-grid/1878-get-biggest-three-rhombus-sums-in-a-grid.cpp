class Solution {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        set<int> top;

        auto addToTop = [&](int val) {
            top.insert(val);
            if (top.size() > 3)
                top.erase(top.begin());
        };

        for (int r = 0; r < m; r++)
            for (int c = 0; c < n; c++) {
                addToTop(grid[r][c]);

                for (int size = 1; r - size >= 0 && r + size < m &&
                                   c - size >= 0 && c + size < n;
                     size++) {
                    int sum = 0;
                    for (int d = 0; d < size; d++) {
                        sum += grid[r - size + d][c + d];
                        sum += grid[r + d][c + size - d];
                        sum += grid[r + size - d][c - d];
                        sum += grid[r - d][c - size + d];
                    }
                    addToTop(sum);
                }
            }

        return vector<int>(top.rbegin(), top.rend());
    }
};