class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        int n = A.size(), common = 0;
        vector<int> cnt(n + 1, 0), ans(n);
        for (int i = 0; i < n; i++) {
            if (++cnt[A[i]] == 2)
                common++;
            if (++cnt[B[i]] == 2)
                common++;
            ans[i] = common;
        }
        return ans;
    }
};