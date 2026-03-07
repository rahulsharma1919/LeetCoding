class Solution {
public:
    int minFlips(string s) {
        int n = s.size();
        string t = s + s;

        int alt1 = 0, alt2 = 0;
        int res = INT_MAX;

        for (int i = 0; i < t.size(); i++) {
            char expected1 = (i % 2) ? '1' : '0';
            char expected2 = (i % 2) ? '0' : '1';

            if (t[i] != expected1)
                alt1++;
            if (t[i] != expected2)
                alt2++;

            if (i >= n) {
                char prev1 = ((i - n) % 2) ? '1' : '0';
                char prev2 = ((i - n) % 2) ? '0' : '1';

                if (t[i - n] != prev1)
                    alt1--;
                if (t[i - n] != prev2)
                    alt2--;
            }

            if (i >= n - 1)
                res = min(res, min(alt1, alt2));
        }

        return res;
    }
};