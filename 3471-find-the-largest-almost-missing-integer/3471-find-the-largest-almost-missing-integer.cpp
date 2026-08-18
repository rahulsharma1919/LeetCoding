class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();
        set<int> distinctVals(nums.begin(), nums.end());

        int ans = -1;

        for (int x : distinctVals) {
            int cnt = 0;
            for (int start = 0; start + k <= n; start++) {
                bool found = false;
                for (int j = start; j < start + k; j++) {
                    if (nums[j] == x) {
                        found = true;
                        break;
                    }
                }
                if (found)
                    cnt++;
            }

            if (cnt == 1) {
                ans = max(ans, x);
            }
        }

        return ans;
    }
};