class Solution {
public:
    bool canBeEqual(string s1, string s2) {
        return sorted2(s1[0], s1[2]) == sorted2(s2[0], s2[2]) &&
               sorted2(s1[1], s1[3]) == sorted2(s2[1], s2[3]);
    }

private:
    pair<char, char> sorted2(char a, char b) {
        return a < b ? make_pair(a, b) : make_pair(b, a);
    }
};