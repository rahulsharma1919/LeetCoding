class Solution {
public:
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        int layers = min(m, n) / 2;

        for (int l = 0; l < layers; l++) {
            vector<int> ring;
            int top = l, bot = m - 1 - l, left = l, right = n - 1 - l;

            for (int c = left; c <= right; c++)
                ring.push_back(grid[top][c]);
            for (int r = top + 1; r <= bot; r++)
                ring.push_back(grid[r][right]);
            for (int c = right - 1; c >= left; c--)
                ring.push_back(grid[bot][c]);
            for (int r = bot - 1; r > top; r--)
                ring.push_back(grid[r][left]);

            int sz = ring.size();
            int shift = k % sz;
            rotate(ring.begin(), ring.begin() + shift, ring.end());

            int idx = 0;
            for (int c = left; c <= right; c++)
                grid[top][c] = ring[idx++];
            for (int r = top + 1; r <= bot; r++)
                grid[r][right] = ring[idx++];
            for (int c = right - 1; c >= left; c--)
                grid[bot][c] = ring[idx++];
            for (int r = bot - 1; r > top; r--)
                grid[r][left] = ring[idx++];
        }

        return grid;
    }
};