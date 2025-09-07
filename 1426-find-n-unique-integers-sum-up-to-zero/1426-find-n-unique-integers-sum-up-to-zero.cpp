class Solution {
public:
    vector<int> sumZero(int n) {
        vector<int> ans(n);
        int left = 0, right = n - 1, num = 1;
        while (left < right) {
            ans[left++] = -num;
            ans[right--] = num;
            num++;
        }
        if (n % 2 == 1) ans[left] = 0; // middle element when odd
        return ans;
    }
};
