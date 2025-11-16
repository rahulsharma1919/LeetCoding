class Solution {
public:
    int numSub(string s) {
        const int MOD = 1'000'000'007;
        long long count = 0;
        long long res = 0;

        for (char c : s) {
            if (c == '1') {
                count++;
                res = (res + count) % MOD;
            } else {
                count = 0;
            }
        }

        return res;
    }
};
