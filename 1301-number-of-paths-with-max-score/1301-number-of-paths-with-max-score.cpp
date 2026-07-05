class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        const int MOD = 1e9 + 7;
        int n = board.size();
        vector<vector<int>> score(n, vector<int>(n, -1));
        vector<vector<long long>> cnt(n, vector<long long>(n, 0));

        score[n - 1][n - 1] = 0;
        cnt[n - 1][n - 1] = 1;

        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (board[i][j] == 'X')
                    continue;
                if (i == n - 1 && j == n - 1)
                    continue;

                int dirs[3][2] = {{1, 0}, {0, 1}, {1, 1}};
                for (auto& d : dirs) {
                    int ni = i + d[0], nj = j + d[1];
                    if (ni >= n || nj >= n)
                        continue;
                    if (score[ni][nj] == -1)
                        continue;
                    int val = score[ni][nj] +
                              (board[i][j] >= '1' && board[i][j] <= '9'
                                   ? board[i][j] - '0'
                                   : 0);
                    if (val > score[i][j]) {
                        score[i][j] = val;
                        cnt[i][j] = cnt[ni][nj];
                    } else if (val == score[i][j]) {
                        cnt[i][j] = (cnt[i][j] + cnt[ni][nj]) % MOD;
                    }
                }
            }
        }

        if (score[0][0] == -1)
            return {0, 0};
        return {score[0][0], (int)(cnt[0][0] % MOD)};
    }
};