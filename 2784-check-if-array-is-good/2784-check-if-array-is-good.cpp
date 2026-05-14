class Solution {
public:
    bool isGood(vector<int>& nums) {
        int n = *max_element(nums.begin(), nums.end());
        if (nums.size() != n + 1)
            return false;
        vector<int> cnt(n + 1, 0);
        for (int v : nums) {
            if (v > n)
                return false;
            cnt[v]++;
        }
        for (int i = 1; i < n; i++)
            if (cnt[i] != 1)
                return false;
        return cnt[n] == 2;
    }
};