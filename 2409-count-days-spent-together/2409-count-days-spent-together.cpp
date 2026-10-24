class Solution {
public:
    int countDaysTogether(string arriveAlice, string leaveAlice,
                          string arriveBob, string leaveBob) {
        static const int pre[12] = {0,   31,  59,  90,  120, 151,
                                    181, 212, 243, 273, 304, 334};
        auto day = [&](const string& s) {
            return pre[(s[0] - '0') * 10 + (s[1] - '0') - 1] +
                   (s[3] - '0') * 10 + (s[4] - '0');
        };
        int lo = max(day(arriveAlice), day(arriveBob));
        int hi = min(day(leaveAlice), day(leaveBob));
        return max(0, hi - lo + 1);
    }
};