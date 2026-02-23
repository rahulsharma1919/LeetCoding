class Solution {
public:
    bool hasAllCodes(string s, int k) {
        int need = 1 << k;
        vector<bool> seen(need, false);

        int mask = 0;
        int allOnes = (1 << k) - 1;
        int count = 0;

        for (int i = 0; i < s.size(); i++) {
            mask = ((mask << 1) & allOnes) | (s[i] - '0');

            if (i >= k - 1 && !seen[mask]) {
                seen[mask] = true;
                count++;
                if (count == need)
                    return true;
            }
        }
        return false;
    }
};