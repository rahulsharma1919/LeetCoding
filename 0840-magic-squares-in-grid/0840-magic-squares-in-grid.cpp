class Solution {
public:
    bool isMagic(vector<vector<int>>& g, int r, int c) {
        vector<int> cnt(10, 0);

        for (int i = r; i < r + 3; i++) {
            for (int j = c; j < c + 3; j++) {
                int v = g[i][j];
                if (v < 1 || v > 9 || ++cnt[v] > 1)
                    return false;
            }
        }

        for (int i = 0; i < 3; i++) {
            if (g[r + i][c] + g[r + i][c + 1] + g[r + i][c + 2] != 15)
                return false;
        }

        for (int j = 0; j < 3; j++) {
            if (g[r][c + j] + g[r + 1][c + j] + g[r + 2][c + j] != 15)
                return false;
        }

        if (g[r][c] + g[r + 1][c + 1] + g[r + 2][c + 2] != 15)
            return false;
        if (g[r][c + 2] + g[r + 1][c + 1] + g[r + 2][c] != 15)
            return false;

        return true;
    }

    int numMagicSquaresInside(vector<vector<int>>& grid) {
        int rows = grid.size(), cols = grid[0].size();
        int count = 0;

        for (int i = 0; i + 2 < rows; i++) {
            for (int j = 0; j + 2 < cols; j++) {
                if (grid[i + 1][j + 1] == 5 && isMagic(grid, i, j))
                    count++;
            }
        }

        return count;
    }
};
