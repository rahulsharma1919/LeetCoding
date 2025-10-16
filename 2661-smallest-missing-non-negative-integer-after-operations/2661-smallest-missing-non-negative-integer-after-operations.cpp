class Solution {
public:
    int findSmallestInteger(vector<int>& nums, int value) {
        vector<int> count(value, 0);
        for (int num : nums) {
            int r = ((num % value) + value) % value;
            count[r]++;
        }

        int mex = 0;
        while (true) {
            int r = mex % value;
            if (count[r] == 0)
                break;
            count[r]--;
            mex++;
        }

        return mex;
    }
};
