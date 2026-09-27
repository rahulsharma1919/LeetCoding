class Solution {
public:
    string reverseParentheses(string s) {
        int n = s.size();
        vector<int> pair(n);
        stack<int> st;

        // match each '(' with its ')'
        for (int i = 0; i < n; i++) {
            if (s[i] == '(')
                st.push(i);
            else if (s[i] == ')') {
                int j = st.top();
                st.pop();
                pair[i] = j;
                pair[j] = i;
            }
        }

        string result;
        result.reserve(n);
        int dir = 1;

        for (int i = 0; i < n; i += dir) {
            if (s[i] == '(' || s[i] == ')') {
                i = pair[i]; // jump to the matching bracket
                dir = -dir;  // and reverse walking direction
            } else {
                result += s[i];
            }
        }

        return result;
    }
};