// class Solution {
// public:
//     vector<int> twoSum(vector<int>& nums, int target) {
//         // traversing till the last element
//         for (int i = 0; i<nums.size(); i++){
//             // another loop from i+1 till the last element
//             for (int j=i+1; j<nums.size(); j++){
//                 // check if pair's sum is equal to target or not 
//                 if (nums[i] + nums[j] == target){
//                     // returning the indices if true 
//                     return {i,j};
//                 }
//             }
//         }   //brute force method
//         return {};  // no solution found
//     }
// };
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> numMap;
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            int complement = target - nums[i];
            if (numMap.count(complement)) {
                return {numMap[complement], i};
            }
            numMap[nums[i]] = i;
        }

        return {}; // No solution found
    }
};