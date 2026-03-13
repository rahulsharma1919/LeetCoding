class Solution {
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        auto maxReduce = [](long long w, long long mid) -> long long {
            return (long long)((-1 + sqrt(1 + 8.0 * mid / w)) / 2);
        };

        auto canFinish = [&](long long mid) {
            long long total = 0;
            for (int w : workerTimes) {
                total += maxReduce(w, mid);
                if (total >= mountainHeight)
                    return true;
            }
            return false;
        };

        long long maxW = *max_element(workerTimes.begin(), workerTimes.end());
        long long lo = 1,
                  hi = maxW * (long long)mountainHeight * (mountainHeight + 1) /
                       2,
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