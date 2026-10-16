class Solution {
public:
    static const long long MOD = 1000000007LL;
    vector<long long> s1, s2, lz;   // sum of d, sum of d^2, pending add (all exact, reduced mod)

    void apply(int o, int len, long long v) {
        // (d+v)^2 = d^2 + 2vd + v^2
        s2[o] = (s2[o] + 2 * v % MOD * s1[o] + (long long)len * (v * v % MOD)) % MOD;
        s1[o] = (s1[o] + (long long)len * v) % MOD;
        lz[o] = (lz[o] + v) % MOD;
    }
    void push(int o, int l, int r) {
        if (!lz[o]) return;
        int m = (l + r) / 2;
        apply(2 * o, m - l + 1, lz[o]);
        apply(2 * o + 1, r - m, lz[o]);
        lz[o] = 0;
    }
    void update(int o, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) { apply(o, r - l + 1, 1); return; }
        push(o, l, r);
        int m = (l + r) / 2;
        if (ql <= m) update(2 * o, l, m, ql, qr);
        if (qr > m) update(2 * o + 1, m + 1, r, ql, qr);
        s1[o] = (s1[2 * o] + s1[2 * o + 1]) % MOD;
        s2[o] = (s2[2 * o] + s2[2 * o + 1]) % MOD;
    }

    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        s1.assign(4 * n, 0); s2.assign(4 * n, 0); lz.assign(4 * n, 0);
        vector<int> last(100001, -1);
        long long ans = 0;
        for (int j = 0; j < n; j++) {
            // starts i in (last[x], j] get one more distinct value
            update(1, 0, n - 1, last[nums[j]] + 1, j);
            last[nums[j]] = j;
            ans = (ans + s2[1]) % MOD;   // positions > j still hold 0
        }
        return (int)ans;
    }
};