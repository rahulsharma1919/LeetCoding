class Solution {
public:
    int minOperations(string s) {
        int n = s.size();
        int change0 = 0, change1 = 0;

        for (int i = 0; i < n; i++) {
            char expected0 = (i % 2 == 0) ? '0' : '1';
            char expected1 = (i % 2 == 0) ? '1' : '0';

            if (s[i] != expected0)
                change0++;
            if (s[i] != expected1)
                change1++;
        }

        return min(change0, change1);
    }
};