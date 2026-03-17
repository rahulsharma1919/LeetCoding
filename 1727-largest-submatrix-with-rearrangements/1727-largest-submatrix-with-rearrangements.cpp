class Solution {
public:
    int largestSubmatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size(), ans = 0;

        for (int r = 1; r < m; r++)
            for (int c = 0; c < n; c++)
                if (matrix[r][c]) matrix[r][c] += matrix[r-1][c];

        for (int r = 0; r < m; r++) {
            vector<int> row = matrix[r];
            sort(row.rbegin(), row.rend());
            for (int c = 0; c < n && row[c]; c++)
                ans = max(ans, row[c] * (c + 1));
        }

        return ans;
    }
};