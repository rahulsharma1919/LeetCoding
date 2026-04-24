class Solution {
public:
    int furthestDistanceFromOrigin(string moves) {
        int L = count(moves.begin(), moves.end(), 'L');
        int R = count(moves.begin(), moves.end(), 'R');
        int blanks = moves.size() - L - R;
        return abs(L - R) + blanks;
    }
};