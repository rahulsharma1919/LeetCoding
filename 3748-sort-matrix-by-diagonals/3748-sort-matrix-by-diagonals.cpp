class Solution {
public:
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        int n = grid.size();

        // helper to collect, sort, and put back one diagonal
        auto processDiagonal = [&](int r, int c, bool nonIncreasing) {
            vector<int> diag;
            int i = r, j = c;
            while (i < n && j < n) {
                diag.push_back(grid[i][j]);
                i++; j++;
            }

            if (nonIncreasing)
                sort(diag.begin(), diag.end(), greater<int>());
            else
                sort(diag.begin(), diag.end());

            i = r, j = c;
            int idx = 0;
            while (i < n && j < n) {
                grid[i][j] = diag[idx++];
                i++; j++;
            }
        };

        // bottom-left triangle (including main diagonal): non-increasing
        for (int i = 0; i < n; i++) {
            processDiagonal(i, 0, true);  // start from left column
        }
        for (int j = 1; j < n; j++) {
            processDiagonal(0, j, false); // top row (excluding [0,0])
        }

        return grid;
    }
};
