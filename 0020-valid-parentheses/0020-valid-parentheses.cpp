class Solution {
public:
    bool isValid(string s) {
        if (s.size() % 2 == 1)
            return false; // odd length can never balance

        stack<char> st;

        for (char c : s) {
            if (c == '(')
                st.push(')');
            else if (c == '{')
                st.push('}');
            else if (c == '[')
                st.push(']');
            else {
                if (st.empty() || st.top() != c)
                    return false;
                st.pop();
            }
        }

        return st.empty();
    }
};