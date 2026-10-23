class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        int k = -1; // all bits set
        for (int i = 0; i < (int)nums.size(); i++)
            if (nums[i] != i)
                k &= nums[i];
        return k == -1 ? 0 : k; // already sorted -> 0
    }
};