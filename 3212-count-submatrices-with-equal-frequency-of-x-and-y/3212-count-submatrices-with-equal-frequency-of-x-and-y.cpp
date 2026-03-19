class Solution {
public:
    int numberOfSubmatrices(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size(), ans = 0;
        vector<vector<int>> diff(m, vector<int>(n, 0));
        vector<vector<int>> xcount(m, vector<int>(n, 0));

        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                int d = (grid[r][c] == 'X') - (grid[r][c] == 'Y');
                int x = (grid[r][c] == 'X');

                diff[r][c] = d + (r ? diff[r - 1][c] : 0) +
                             (c ? diff[r][c - 1] : 0) -
                             (r && c ? diff[r - 1][c - 1] : 0);
                xcount[r][c] = x + (r ? xcount[r - 1][c] : 0) +
                               (c ? xcount[r][c - 1] : 0) -
                               (r && c ? xcount[r - 1][c - 1] : 0);

                if (diff[r][c] == 0 && xcount[r][c] > 0)
                    ans++;
            }
        }

        return ans;
    }
};