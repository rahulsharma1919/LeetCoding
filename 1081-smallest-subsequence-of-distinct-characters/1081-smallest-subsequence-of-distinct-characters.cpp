class Solution {
public:
    string smallestSubsequence(string s) {
        int last[26] = {};
        for (int i = 0; i < s.size(); i++)
            last[s[i] - 'a'] = i;

        bool inStack[26] = {};
        string st;
        for (int i = 0; i < s.size(); i++) {
            int c = s[i] - 'a';
            if (inStack[c])
                continue;
            while (!st.empty() && st.back() > s[i] &&
                   last[st.back() - 'a'] > i) {
                inStack[st.back() - 'a'] = false;
                st.pop_back();
            }
            st += s[i];
            inStack[c] = true;
        }
        return st;
    }
};