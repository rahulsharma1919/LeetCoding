class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size(), m = word2.size();

        vector<int> suf(n + 1, 0); // suf[n] = 0 by default
        int j = m - 1;
        for (int i = n - 1; i >= 0; i--) {
            if (j >= 0 && word1[i] == word2[j]) {
                j--;
            }
            suf[i] = m - 1 - j;
        }

        vector<int> result(m, -1);
        int i = 0;
        bool changed = false;

        for (int k = 0; k < m; k++) {
            if (i < n && word1[i] == word2[k]) {
                result[k] = i;
                i++;
            } else if (!changed && i < n && suf[i + 1] >= m - 1 - k) {
                result[k] = i;
                i++;
                changed = true;
            } else {
                while (i < n && word1[i] != word2[k])
                    i++;
                if (i >= n)
                    return {};
                result[k] = i;
                i++;
            }
        }

        return result;
    }
};