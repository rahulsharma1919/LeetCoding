class Solution {
public:
    int minInsertions(string s) {
        int n = s.size(), open = 0, ins = 0;

        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                open++;
            } else {
                if (i + 1 < n && s[i + 1] == ')')
                    i++;
                else
                    ins++;

                if (open)
                    open--;
                else
                    ins++;
            }
        }

        return ins + 2 * open;
    }
};