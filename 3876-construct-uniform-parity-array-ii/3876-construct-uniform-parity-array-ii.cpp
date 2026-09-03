class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int n = nums1.size();
        int minVal = INT_MAX;
        bool hasOdd = false;

        for (int x : nums1) {
            minVal = min(minVal, x);
            if (x % 2 == 1)
                hasOdd = true;
        }

        if (!hasOdd)
            return true;

        if (minVal % 2 == 1)
            return true;

        return false;
    }
};