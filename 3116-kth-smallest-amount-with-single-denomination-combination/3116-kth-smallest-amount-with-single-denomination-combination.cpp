class Solution {
public:
    long long findKthSmallest(vector<int>& coins, int k) {
        int n = coins.size();
        vector<long long> lcmSubset(1 << n, 0);
        lcmSubset[0] = 0;

        for (int mask = 1; mask < (1 << n); mask++) {
            int lowBit = mask & (-mask);
            int idx = __builtin_ctz(lowBit);
            int rest = mask ^ lowBit;

            if (rest == 0) {
                lcmSubset[mask] = coins[idx];
            } else {
                long long g = std::gcd((long long)coins[idx], lcmSubset[rest]);
                long long l = (long long)coins[idx] / g * lcmSubset[rest];
                // guard against overflow blowup — cap if it exceeds a safe
                // bound
                if (l > (long long)2e18)
                    l = (long long)2e18;
                lcmSubset[mask] = l;
            }
        }

        auto countAtMost = [&](long long x) -> long long {
            long long count = 0;
            for (int mask = 1; mask < (1 << n); mask++) {
                int bits = __builtin_popcount(mask);
                long long l = lcmSubset[mask];
                long long term = x / l;
                if (bits % 2 == 1)
                    count += term;
                else
                    count -= term;
            }
            return count;
        };

        long long lo = 1, hi = (long long)25 *
                               k; // safe upper bound (smallest coin ≤25)
        while (lo < hi) {
            long long mid = lo + (hi - lo) / 2;
            if (countAtMost(mid) >= k) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }

        return lo;
    }
};