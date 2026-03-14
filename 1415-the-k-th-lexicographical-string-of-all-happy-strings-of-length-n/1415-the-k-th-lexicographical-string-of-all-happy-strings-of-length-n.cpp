class Solution {
public:
    string getHappyString(int n, int k) {
        int total = 3 * (1 << (n - 1));
        if (k > total)
            return "";

        string result = "";
        k--;

        for (int i = 0; i < n; i++) {
            int subtree = 1 << (n - 1 - i);
            string choices = i == 0 ? "abc"
                                    : (result.back() == 'a'   ? "bc"
                                       : result.back() == 'b' ? "ac"
                                                              : "ab");

            int idx = k / subtree;
            result += choices[idx];
            k %= subtree;
        }

        return result;
    }
};