class Solution {
public:
    string generateString(string str1, string str2) {
        int n = str1.size(), m = str2.size(), total = n + m - 1;
        string word(total, 'a');
        vector<bool> forced(total, false);

        for (int i = 0; i < n; i++) {
            if (str1[i] == 'T') {
                for (int j = 0; j < m; j++) {
                    if (forced[i + j] && word[i + j] != str2[j])
                        return "";
                    word[i + j] = str2[j];
                    forced[i + j] = true;
                }
            }
        }
        vector<int> fail(m, 0);
        for (int i = 1; i < m; i++) {
            int j = fail[i - 1];
            while (j > 0 && str2[i] != str2[j])
                j = fail[j - 1];
            if (str2[i] == str2[j])
                j++;
            fail[i] = j;
        }

        vector<bool> matches(n, false);
        int j = 0;
        for (int i = 0; i < total; i++) {
            while (j > 0 && word[i] != str2[j])
                j = fail[j - 1];
            if (word[i] == str2[j])
                j++;
            if (j == m) {
                int start = i - m + 1;
                if (start < n)
                    matches[start] = true;
                j = fail[j - 1];
            }
        }

        for (int i = 0; i < n; i++) {
            if (str1[i] == 'F' && matches[i]) {
                int fix = -1;
                for (int k = i + m - 1; k >= i; k--) {
                    if (!forced[k]) {
                        fix = k;
                        break;
                    }
                }
                if (fix == -1)
                    return "";
                char bad = str2[fix - i];
                word[fix] = (bad == 'a') ? 'b' : 'a';
                int restart = max(0, fix - m + 1);
                j = 0;
                fill(matches.begin(), matches.end(), false);
                j = 0;
                for (int ii = 0; ii < total; ii++) {
                    while (j > 0 && word[ii] != str2[j])
                        j = fail[j - 1];
                    if (word[ii] == str2[j])
                        j++;
                    if (j == m) {
                        int start = ii - m + 1;
                        if (start < n)
                            matches[start] = true;
                        j = fail[j - 1];
                    }
                }
            }
        }

        for (int i = 0; i < n; i++)
            if (str1[i] == 'F' && matches[i])
                return "";

        return word;
    }
};