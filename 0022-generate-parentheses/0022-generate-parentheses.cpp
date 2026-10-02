class Solution {
public:
    vector<string> result;
    string cur;

    void backtrack(int open, int close, int n) {
        if ((int)cur.size() == 2 * n) {
            result.push_back(cur);
            return;
        }

        if (open < n) { // can still place an '('
            cur.push_back('(');
            backtrack(open + 1, close, n);
            cur.pop_back();
        }

        if (close < open) { // can only close if there's an unmatched '('
            cur.push_back(')');
            backtrack(open, close + 1, n);
            cur.pop_back();
        }
    }

    vector<string> generateParenthesis(int n) {
        cur.reserve(2 * n);
        backtrack(0, 0, n);
        return result;
    }
};