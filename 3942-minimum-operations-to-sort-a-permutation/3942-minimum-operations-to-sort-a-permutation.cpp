class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        if (n <= 2)
            return nums[0] == 0 ? 0 : 1; // [0],[0,1] sorted; [1,0] needs one op

        bool asc = true, desc = true;
        for (int i = 0; i < n; i++) {
            if (nums[i] != (nums[0] + i) % n)
                asc = false;
            if (nums[i] != ((nums[0] - i) % n + n) % n)
                desc = false;
        }

        if (asc) {
            int k = (n - nums[0]) % n; // left rotations needed
            if (k == 0)
                return 0;
            return min(k, n - k + 2); // or reverse, rotate, reverse
        }
        if (desc) {
            int j = 0;
            while (nums[j] != n - 1)
                j++; // position of the maximum
            return 1 +
                   min(j, (n - j) % n); // one reverse plus the cheaper rotation
        }
        return -1;
    }
};