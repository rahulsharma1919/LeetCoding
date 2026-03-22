class Solution {
public:
    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
        int n = mat.size();

        auto rotate = [&]() {
            for (int r = 0; r < n / 2; r++)
                for (int c = r; c < n - 1 - r; c++) {
                    int tmp = mat[r][c];
                    mat[r][c] = mat[n - 1 - c][r];
                    mat[n - 1 - c][r] = mat[n - 1 - r][n - 1 - c];
                    mat[n - 1 - r][n - 1 - c] = mat[c][n - 1 - r];
                    mat[c][n - 1 - r] = tmp;
                }
        };

        for (int i = 0; i < 4; i++) {
            if (mat == target)
                return true;
            rotate();
        }
        return false;
    }
};