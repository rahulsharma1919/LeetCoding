class Solution {
public:
    int countCollisions(string directions) {
        int n = directions.size();
        int left = 0, right = n - 1;

        // trim safe left-moving cars
        while (left < n && directions[left] == 'L')
            left++;

        // trim safe right-moving cars
        while (right >= 0 && directions[right] == 'R')
            right--;

        int collisions = 0;

        // count non-S inside trimmed region
        for (int i = left; i <= right; i++) {
            if (directions[i] != 'S')
                collisions++;
        }

        return collisions;
    }
};
