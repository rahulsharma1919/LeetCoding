class Solution {
public:
    int countPartitions(vector<int>& nums, int k) {
        const int MOD = 1e9 + 7;
        int n = nums.size();

        vector<long long> dp(n + 1, 0), pref(n + 1, 0);
        dp[0] = 1;
        pref[0] = 1;

        deque<int> maxdq, mindq;
        int left = 0;

        for (int right = 0; right < n; right++) {
            // maintain max deque
            while (!maxdq.empty() && nums[maxdq.back()] < nums[right])
                maxdq.pop_back();
            maxdq.push_back(right);

            // maintain min deque
            while (!mindq.empty() && nums[mindq.back()] > nums[right])
                mindq.pop_back();
            mindq.push_back(right);

            // shrink window until valid
            while (!maxdq.empty() && !mindq.empty() &&
                   nums[maxdq.front()] - nums[mindq.front()] > k) {

                if (maxdq.front() == left)
                    maxdq.pop_front();
                if (mindq.front() == left)
                    mindq.pop_front();
                left++;
            }

            // dp transition
            dp[right + 1] = pref[right] - (left > 0 ? pref[left - 1] : 0);
            dp[right + 1] = (dp[right + 1] + MOD) % MOD;

            pref[right + 1] = (pref[right] + dp[right + 1]) % MOD;
        }

        return dp[n];
    }
};
