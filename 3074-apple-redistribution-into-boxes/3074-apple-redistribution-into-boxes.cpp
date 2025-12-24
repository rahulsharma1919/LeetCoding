class Solution {
public:
    int minimumBoxes(vector<int>& apple, vector<int>& capacity) {
        int totalApples = 0;
        for (int a : apple)
            totalApples += a;

        sort(capacity.begin(), capacity.end(), greater<int>());

        int used = 0;
        int sumCap = 0;
        for (int c : capacity) {
            sumCap += c;
            used++;
            if (sumCap >= totalApples)
                break;
        }

        return used;
    }
};
