class Solution {
public:
    int longestBalanced(string s) {
        int n = s.size();
        int ans = 1;

        for (int i = 0; i < n;) {
            int j = i;
            while (j < n && s[j] == s[i])
                j++;
            ans = max(ans, j - i);
            i = j;
        }

        auto solveTwo = [&](char x, char y, char bad) {
            int best = 0;
            int i = 0;
            while (i < n) {
                if (s[i] == bad) {
                    i++;
                    continue;
                }
                unordered_map<int, int> first;
                first[0] = i - 1;
                int diff = 0;
                int j = i;
                while (j < n && s[j] != bad) {
                    if (s[j] == x)
                        diff++;
                    if (s[j] == y)
                        diff--;
                    if (first.count(diff))
                        best = max(best, j - first[diff]);
                    else
                        first[diff] = j;
                    j++;
                }
                i = j;
            }
            return best;
        };

        ans = max(ans, solveTwo('a', 'b', 'c'));
        ans = max(ans, solveTwo('a', 'c', 'b'));
        ans = max(ans, solveTwo('b', 'c', 'a'));

        unordered_map<long long, int> first;
        long long key = 0;
        first[0] = -1;
        int ca = 0, cb = 0, cc = 0;

        for (int i = 0; i < n; i++) {
            if (s[i] == 'a')
                ca++;
            else if (s[i] == 'b')
                cb++;
            else
                cc++;

            int d1 = ca - cb;
            int d2 = ca - cc;
            key = ((long long)d1 << 32) ^ (unsigned int)d2;

            if (first.count(key))
                ans = max(ans, i - first[key]);
            else
                first[key] = i;
        }

        return ans;
    }
};
