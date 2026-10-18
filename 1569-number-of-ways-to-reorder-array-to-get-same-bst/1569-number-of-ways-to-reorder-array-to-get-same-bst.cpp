class Solution {
public:
    static const int MOD = 1000000007;
    int C[1001][1001];

    long long solve(vector<int>& a) {
        int n = a.size();
        if (n <= 2)
            return 1;
        vector<int> L, R;
        for (int i = 1; i < n; i++)
            (a[i] < a[0] ? L : R).push_back(a[i]);
        long long res = C[n - 1][L.size()];
        res = res * solve(L) % MOD;
        res = res * solve(R) % MOD;
        return res;
    }

    int numOfWays(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i <= n; i++) {
            C[i][0] = 1;
            for (int j = 1; j <= i; j++)
                C[i][j] =
                    (C[i - 1][j - 1] + (j <= i - 1 ? C[i - 1][j] : 0)) % MOD;
        }
        return (int)((solve(nums) - 1 + MOD) % MOD);
    }
};