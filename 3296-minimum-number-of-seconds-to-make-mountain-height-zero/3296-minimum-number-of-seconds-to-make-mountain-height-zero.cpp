class Solution {
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        auto timeToReduce = [](long long w, long long x) {
            return w * x * (x + 1) / 2;
        };

        auto canFinish = [&](long long mid) {
            long long totalReduction = 0;
            for (int w : workerTimes) {
                long long lo = 1, hi = mountainHeight, best = 0;
                while (lo <= hi) {
                    long long x = lo + (hi - lo) / 2;
                    if (timeToReduce(w, x) <= mid) {
                        best = x;
                        lo = x + 1;
                    } else {
                        hi = x - 1;
                    }
                }
                totalReduction += best;
                if (totalReduction >= mountainHeight)
                    return true;
            }
            return totalReduction >= mountainHeight;
        };

        long long lo = 1,
                  hi = timeToReduce(
                      *max_element(workerTimes.begin(), workerTimes.end()),
                      mountainHeight),
                  ans = hi;
        while (lo <= hi) {
            long long mid = lo + (hi - lo) / 2;
            if (canFinish(mid)) {
                ans = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }

        return ans;
    }
};