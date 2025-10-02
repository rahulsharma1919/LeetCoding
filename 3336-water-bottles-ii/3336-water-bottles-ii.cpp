class Solution {
public:
    int maxBottlesDrunk(int numBottles, int numExchange) {
        int drank = numBottles;
        int empty = numBottles;
        
        while (empty >= numExchange) {
            empty -= numExchange;
            numExchange++;
            drank++;
            empty++;
        }
        
        return drank;
    }
};
