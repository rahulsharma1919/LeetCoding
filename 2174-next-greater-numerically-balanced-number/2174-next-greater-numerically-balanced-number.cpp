class Solution {
public:
    bool isBalanced(int n) {
        string s = to_string(n);
        vector<int> freq(10, 0);
        for (char c : s) freq[c - '0']++;
        for (int i = 0; i < 10; i++) 
            if (freq[i] && freq[i] != i) return false;
        return true;
    }

    int nextBeautifulNumber(int n) {
        for (int i = n + 1; ; i++)
            if (isBalanced(i)) return i;
    }
};
