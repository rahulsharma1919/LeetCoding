class Solution {
public:
    vector<int> maxValue(vector<int>& nums) {
        int n = nums.size();

        vector<int> suffixMin(n);
        suffixMin[n - 1] = nums[n - 1];

        for (int i = n - 2; i >= 0; --i) {
            suffixMin[i] = min(suffixMin[i + 1], nums[i]);
        }

        vector<int> ans(n);

        int start = 0;
        int prefMax = nums[0];
        int compMax = nums[0];

        for (int i = 0; i < n - 1; ++i) {
            prefMax = max(prefMax, nums[i]);
            compMax = max(compMax, nums[i]);

            // No inversion across this cut => different components
            if (prefMax <= suffixMin[i + 1]) {
                compMax = max(compMax, nums[i]);

                for (int j = start; j <= i; ++j) {
                    ans[j] = compMax;
                }

                start = i + 1;
                if (start < n) {
                    prefMax = nums[start];
                    compMax = nums[start];
                }
            }
        }

        // Last component
        compMax = nums[start];
        for (int i = start; i < n; ++i) {
            compMax = max(compMax, nums[i]);
        }

        for (int i = start; i < n; ++i) {
            ans[i] = compMax;
        }

        return ans;
    }
};