class Solution {
public:
    bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
        sort(begin(asteroids), end(asteroids));
        long long m = mass;
        for (int a : asteroids) {
            if (m < a)
                return false;
            m += a;
        }
        return true;
    }
};