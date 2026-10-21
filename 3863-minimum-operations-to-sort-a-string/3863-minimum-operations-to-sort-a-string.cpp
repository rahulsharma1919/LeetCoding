class Solution {
public:
    int minOperations(string s) {
        int n = s.size();
        if (is_sorted(s.begin(), s.end()))
            return 0;
        if (n == 2)
            return -1;

        char mn = *min_element(s.begin(), s.end());
        char mx = *max_element(s.begin(), s.end());

        if (s[0] == mn || s[n - 1] == mx)
            return 1;

        if (s[0] != mx || s[n - 1] != mn)
            return 2;

        for (int i = 1; i + 1 < n; i++)
            if (s[i] == mn || s[i] == mx)
                return 2;
        if (s[0] == mn)
            return 1; // unreachable, kept for clarity
        return 3;
    }
};