class Solution {
public:
    string findTheString(vector<vector<int>>& lcp) {
        int n = lcp.size();
        string word(n, 0);

        int ch = 0;
        for (int i = 0; i < n; i++) {
            if (word[i])
                continue;
            if (ch > 25)
                return "";
            word[i] = 'a' + ch++;
            for (int j = i + 1; j < n; j++)
                if (lcp[i][j] > 0)
                    word[j] = word[i];
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int expected =
                    (word[i] != word[j])
                        ? 0
                        : 1 + (i + 1 < n && j + 1 < n ? lcp[i + 1][j + 1] : 0);
                if (lcp[i][j] != expected)
                    return "";
            }
        }

        return word;
    }
};