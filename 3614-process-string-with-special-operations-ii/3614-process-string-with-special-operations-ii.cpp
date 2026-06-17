class Solution {
public:
    char processStr(string s, long long k) {
        const long long CAP = 2e15;
        int n = s.size();

        vector<long long> lens(n + 1, 0);
        lens[0] = 0;
        for (int i = 0; i < n; i++) {
            char c = s[i];
            if (c == '*')
                lens[i + 1] = max(0LL, lens[i] - 1);
            else if (c == '#')
                lens[i + 1] = min(CAP, lens[i] * 2);
            else if (c == '%')
                lens[i + 1] = lens[i];
            else
                lens[i + 1] = lens[i] + 1;
        }

        if (k >= lens[n])
            return '.';

        long long pos = k;
        for (int i = n - 1; i >= 0; i--) {
            char c = s[i];
            long long cur = lens[i + 1];
            long long prv = lens[i];

            if (c == '#') {
                if (pos >= prv)
                    pos -= prv;
            } else if (c == '%') {
                pos = prv - 1 - pos;
            } else if (c == '*') {
            } else {
                if (pos == prv) {
                    return c;
                }
            }
        }

        return '.';
    }
};