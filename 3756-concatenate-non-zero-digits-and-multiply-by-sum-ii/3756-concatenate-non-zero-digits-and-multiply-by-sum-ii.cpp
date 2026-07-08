class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        const long long MOD = 1e9 + 7;
        int m = s.size();

        vector<long long> preSum(m + 1, 0), preX(m + 1, 0), pow10(m + 1);
        vector<int> preNZ(m + 1, 0);

        pow10[0] = 1;
        for (int i = 1; i <= m; i++)
            pow10[i] = pow10[i - 1] * 10 % MOD;

        for (int i = 0; i < m; i++) {
            int d = s[i] - '0';
            preSum[i + 1] = preSum[i];
            preX[i + 1] = preX[i];
            preNZ[i + 1] = preNZ[i];
            if (d != 0) {
                preSum[i + 1] += d;
                preX[i + 1] = (preX[i] * 10 + d) % MOD;
                preNZ[i + 1]++;
            }
        }

        vector<int> ans;
        ans.reserve(queries.size());
        for (auto& q : queries) {
            int l = q[0], r = q[1];
            long long sum = (preSum[r + 1] - preSum[l] + MOD) % MOD;
            int nz = preNZ[r + 1] - preNZ[l];
            long long x = (preX[r + 1] - preX[l] * pow10[nz] % MOD + MOD) % MOD;
            ans.push_back((int)(x * sum % MOD));
        }
        return ans;
    }
};