class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> cnt;
        for (int x : nums)
            cnt[x]++;

        int ans = 1;

        if (cnt.count(1)) {
            int c = cnt[1];
            ans = max(ans, c % 2 == 0 ? c - 1 : c);
        }

        for (auto& [x, c] : cnt) {
            if (x == 1)
                continue;

            long long cur = x;
            int pairs = 0;

            while (cnt.count(cur) && cnt[cur] >= 2) {
                pairs++;
                if (cur > 1e9) {
                    cur *= cur;
                    break;
                }
                cur = cur * cur;
            }

            int len = 2 * pairs;
            if (cnt.count(cur) && cnt[cur] >= 1)
                len++;
            if (len == 2 * pairs && pairs > 0)
                len = 2 * pairs - 1;

            ans = max(ans, max(len, 1));
        }

        return ans;
    }
};