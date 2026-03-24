class Solution {
public:
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int total = n * m;
        const int MOD = 12345;

        vector<vector<int>> p(n, vector<int>(m));

        long long prefix = 1;
        for (int k = 0; k < total; k++) {
            p[k / m][k % m] = prefix;
            prefix = prefix * (grid[k / m][k % m] % MOD) % MOD;
        }

        long long suffix = 1;
        for (int k = total - 1; k >= 0; k--) {
            p[k / m][k % m] = p[k / m][k % m] * suffix % MOD;
            suffix = suffix * (grid[k / m][k % m] % MOD) % MOD;
        }

        return p;
    }
};