#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxPower(vector<int>& stations, int r, int k) {
        int n = stations.size();
        vector<long long> pref(n + 1, 0);
        for (int i = 0; i < n; ++i)
            pref[i + 1] = pref[i] + stations[i];
        vector<long long> power(n);
        for (int i = 0; i < n; ++i) {
            int L = max(0, i - r);
            int R = min(n - 1, i + r);
            power[i] = pref[R + 1] - pref[L];
        }

        long long sumStations = pref[n];
        long long low = 0,
                  high = sumStations + k; 
        long long ans = 0;
        while (low <= high) {
            long long mid = (low + high) / 2;
            if (canAchieve(mid, power, r, k)) {
                ans = mid;
                low = mid + 1;
            } else
                high = mid - 1;
        }
        return ans;
    }

private:
    bool canAchieve(long long target, const vector<long long>& power, int r,
                    long long k) {
        int n = power.size();
        vector<long long> diff(
            n + 1, 0); 
        long long used = 0;
        long long cur = 0; 
        for (int i = 0; i < n; ++i) {
            cur += diff[i]; 
            long long have = power[i] + cur;
            if (have < target) {
                long long need = target - have;
                used += need;
                if (used > k)
                    return false;
                cur += need;
                int expire = min(n, i + 2 * r + 1);
                diff[expire] -=
                    need; 
            }
        }
        return true;
    }
};
