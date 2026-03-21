class Solution {
public:
    vector<vector<int>> reverseSubmatrix(vector<vector<int>>& grid, int x,
                                         int y, int k) {
        for (int top = x, bot = x + k - 1; top < bot; top++, bot--)
            for (int c = y; c < y + k; c++)
                swap(grid[top][c], grid[bot][c]);
        return grid;
    }
};