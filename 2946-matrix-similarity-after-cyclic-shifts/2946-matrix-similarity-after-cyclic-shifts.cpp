class Solution {
public:
    bool areSimilar(vector<vector<int>>& mat, int k) {
        int m = mat.size(), n = mat[0].size();
        k %= n;
        if (k == 0)
            return true;

        for (int r = 0; r < m; r++)
            for (int c = 0; c < n; c++)
                if (mat[r][c] != mat[r][(c + (r % 2 == 0 ? k : n - k)) % n])
                    return false;

        return true;
    }
};