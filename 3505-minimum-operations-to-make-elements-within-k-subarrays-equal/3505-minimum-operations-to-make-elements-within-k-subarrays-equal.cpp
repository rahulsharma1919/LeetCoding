class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();
        vector<int> v(nums.begin(), nums.end());
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        int M = v.size();
        vector<int> cnt(M + 1, 0);
        vector<long long> sm(M + 1, 0);
        auto rk = [&](int a) {
            return int(lower_bound(v.begin(), v.end(), a) - v.begin()) + 1;
        };
        auto upd = [&](int a, int dc) {
            for (int i = rk(a); i <= M; i += i & -i) {
                cnt[i] += dc;
                sm[i] += (long long)dc * a;
            }
        };
        int LOG = 1;
        while ((1 << LOG) <= M)
            LOG++;
        int need = (x + 1) / 2;

        int W = n - x + 1;
        vector<long long> cost(W);
        long long T = 0;
        for (int i = 0; i < n; i++) {
            upd(nums[i], 1);
            T += nums[i];
            if (i >= x) {
                upd(nums[i - x], -1);
                T -= nums[i - x];
            }
            if (i >= x - 1) {
                int pos = 0, c = 0;
                long long s = 0;
                for (int b = LOG; b >= 0; b--) {
                    int np = pos + (1 << b);
                    if (np <= M && c + cnt[np] < need) {
                        pos = np;
                        c += cnt[np];
                        s += sm[np];
                    }
                }
                long long m = v[pos];
                long long SL = s + (long long)(need - c) * m;
                long long SU = T - SL;
                cost[i - x + 1] = m * need - SL + SU - m * (x - need);
            }
        }

        const long long INF = (long long)1e18;
        vector<long long> prev(n + 1, 0), cur(n + 1);
        for (int j = 1; j <= k; j++) {
            for (int i = 0; i <= n; i++) {
                cur[i] = INF;
                if (i >= 1)
                    cur[i] = cur[i - 1];
                if (i >= x && prev[i - x] < INF)
                    cur[i] = min(cur[i], prev[i - x] + cost[i - x]);
            }
            swap(prev, cur);
        }
        return prev[n];
    }
};