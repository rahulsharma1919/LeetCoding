class Solution {
public:
    int bestClosingTime(string customers) {
        int n = customers.size();

        // Count total 'Y' initially (penalty if shop is closed at hour 0)
        int penalty = 0;
        for (char c : customers) {
            if (c == 'Y')
                penalty++;
        }

        int minPenalty = penalty;
        int bestHour = 0;

        for (int i = 0; i < n; i++) {
            // Moving closing time from i to i+1
            if (customers[i] == 'Y')
                penalty--; // fewer missed customers
            else
                penalty++; // extra hour open with no customer

            if (penalty < minPenalty) {
                minPenalty = penalty;
                bestHour = i + 1;
            }
        }

        return bestHour;
    }
};
