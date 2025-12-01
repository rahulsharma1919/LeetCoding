class Solution {
public:
    long long maxRunTime(int n, vector<int>& batteries) {
        long long sum = 0;
        for (long long b : batteries)
            sum += b;

        long long left = 0, right = sum / n; // maximum possible time

        auto canRun = [&](long long T) {
            long long total = 0;
            for (long long b : batteries) {
                total += min(b, T);
                if (total >= T * n)
                    return true;
            }
            return total >= T * n;
        };

        while (left < right) {
            long long mid = (left + right + 1) / 2;
            if (canRun(mid))
                left = mid;
            else
                right = mid - 1;
        }

        return left;
    }
};
