class Solution {
public:
    vector<string> res;

    void dfs(const string& s, int lastI, int lastJ, char open, char close) {
        int bal = 0;
        for (int i = lastI; i < (int)s.size(); i++) {
            if (s[i] == open)
                bal++;
            else if (s[i] == close)
                bal--;
            if (bal >= 0)
                continue;

            for (int j = lastJ; j <= i; j++) {
                if (s[j] == close && (j == lastJ || s[j - 1] != close)) {
                    dfs(s.substr(0, j) + s.substr(j + 1), i, j, open, close);
                }
            }
            return;
        }

        string rev(s.rbegin(), s.rend());
        if (open == '(')
            dfs(rev, 0, 0, ')', '(');
        else
            res.push_back(rev);
    }

    vector<string> removeInvalidParentheses(string s) {
        dfs(s, 0, 0, '(', ')');
        return res;
    }
};