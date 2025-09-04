class Solution {
public:
    int findClosest(int x, int y, int z) {
        int d1 = abs(x - z);  // distance of Person 1 from Person 3
        int d2 = abs(y - z);  // distance of Person 2 from Person 3

        if (d1 < d2) return 1;   // Person 1 is closer
        else if (d2 < d1) return 2;  // Person 2 is closer
        else return 0;   // both arrive at the same time
    }
};
