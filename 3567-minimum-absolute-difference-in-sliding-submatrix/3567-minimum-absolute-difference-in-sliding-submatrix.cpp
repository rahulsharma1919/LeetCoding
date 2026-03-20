class Solution {
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        int rows = m - k + 1, cols = n - k + 1;
        vector<vector<int>> ans(rows, vector<int>(cols, 0));

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                vector<int> vals;
                vals.reserve(k * k);
                for (int r = i; r < i + k; r++)
                    for (int c = j; c < j + k; c++)
                        vals.push_back(grid[r][c]);

                sort(vals.begin(), vals.end());
                vals.erase(unique(vals.begin(), vals.end()), vals.end());

                if (vals.size() == 1) {
                    ans[i][j] = 0;
                    continue;
                }

                int minDiff = INT_MAX;
                for (int x = 1; x < vals.size(); x++)
                    minDiff = min(minDiff, vals[x] - vals[x - 1]);
                ans[i][j] = minDiff;
            }
        }

        return ans;
    }
};