class Solution {
public:
    int bitwiseComplement(int n) {
        int m = n;    // store n in another variable
        int mask = 0; // initialise a variable mask

        if (n == 0)
            return 1; // edge case

        while (m != 0) {            // loop till m becomes 0
            mask = (mask << 1) | 1; // left shift mask then or with 1 every time
            m = m >> 1;             // update m by doing right shift
        }

        int ans = (~n) & mask; // not n and with mask to create required bit and
                               // store it in variable
        return ans;
    }
};