class Solution {
public:
    int minimumDeletions(string s) {
        int bCount = 0; // number of 'b's seen so far
        int deletions = 0;

        for (char c : s) {
            if (c == 'b') {
                bCount++;
            } else { // c == 'a'
                deletions = min(deletions + 1, bCount);
            }
        }
        return deletions;
    }
};
