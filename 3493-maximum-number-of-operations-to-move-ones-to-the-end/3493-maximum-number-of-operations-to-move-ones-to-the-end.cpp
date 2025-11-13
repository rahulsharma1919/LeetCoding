class Solution {
public:
    int maxOperations(string s) {
        long long ans = 0;   // use long long to be safe for large counts
        long long ones = 0;
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            if (s[i] == '1') {
                ++ones;
            } else {
                if (i + 1 == n || s[i + 1] == '1') {
                    ans += ones;
                }
            }
        }
        return (int)ans;
    }
};