class Solution {
public:
    int countTrapezoids(vector<vector<int>>& points) {
        const long long MOD = 1'000'000'007;

        unordered_map<long long, long long> freq;
        freq.reserve(points.size() * 2);

        for (auto& p : points) {
            freq[p[1]]++;
        }

        long long sumSeg = 0, sumSegSq = 0;

        for (auto& [y, f] : freq) {
            if (f >= 2) {
                long long seg = f * (f - 1) / 2; // C(f,2)
                seg %= MOD;
                sumSeg = (sumSeg + seg) % MOD;
                sumSegSq = (sumSegSq + (seg * seg) % MOD) % MOD;
            }
        }

        long long S2 = (sumSeg * sumSeg) % MOD;

        long long ans = (S2 - sumSegSq + MOD) % MOD;
        ans = (ans * ((MOD + 1) / 2)) % MOD; // divide by 2 mod MOD

        return (int)ans;
    }
};
