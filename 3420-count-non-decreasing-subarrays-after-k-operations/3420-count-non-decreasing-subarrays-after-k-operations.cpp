class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> nxt(n, n);
        vector<int> st;
        // Step 1: Find next greater element
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.back()] <= nums[i]) {
                st.pop_back();
            }

            if (!st.empty()) {
                nxt[i] = st.back();
            }

            st.push_back(i);
        }
        // Prefix sum
        vector<long long> pref(n + 1, 0);
        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + nums[i];
        }
        // Step 2: Binary lifting preparation
        int LOG = 1;
        while ((1 << LOG) <= n) {
            LOG++;
        }
        vector<vector<int>> up(LOG, vector<int>(n + 1, n));
        vector<vector<long long>> cost(LOG, vector<long long>(n + 1, 0));
        for (int i = 0; i < n; i++) {
            up[0][i] = nxt[i];

            cost[0][i] =
                1LL * nums[i] * (nxt[i] - i) - (pref[nxt[i]] - pref[i]);
        }
        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i < n; i++) {
                int mid = up[j - 1][i];

                up[j][i] = up[j - 1][mid];

                cost[j][i] = cost[j - 1][i] + cost[j - 1][mid];
            }
        }
        // Step 3: Calculate operations for [l, r]
        auto getCost = [&](int l, int r) -> long long {
            long long ans = 0;
            int pos = l;
            for (int j = LOG - 1; j >= 0; j--) {
                if (up[j][pos] <= r + 1) {
                    ans += cost[j][pos];
                    pos = up[j][pos];
                }
            }
            // Remaining partial block
            if (pos <= r) {
                ans +=
                    1LL * nums[pos] * (r - pos + 1) - (pref[r + 1] - pref[pos]);
            }
            return ans;
        };
        // Step 4: Sliding window
        long long ans = 0;
        int r = 0;
        for (int l = 0; l < n; l++) {
            if (r < l) {
                r = l;
            }
            while (r + 1 < n && getCost(l, r + 1) <= k) {
                r++;
            }
            ans += r - l + 1;
        }
        return ans;
    }
};