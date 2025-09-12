class Solution {
public:
    bool doesAliceWin(string s) {
        for (char c : s) {
            if (c=='a' || c=='e' || c=='i' || c=='o' || c=='u') {
                return true; // Alice can win by starting with a vowel substring
            }
        }
        return false; // No vowels, Alice cannot make any move
    }
};
