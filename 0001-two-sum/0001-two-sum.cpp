class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        for (int i = 0; i<nums.size(); i++){
            for (int j=i+1; j<nums.size(); j++){
                if (nums[i] + nums[j] == target){
                    return {i,j};
                }
            }
        }
        return {};
    }
};
// class Solution {
// public:
//     vector<int> twoSum(vector<int>& nums, int target) {
//         unordered_map<int, int> numMap;
//         int n = nums.size();

//         for (int i = 0; i < n; i++) {
//             int complement = target - nums[i];
//             if (numMap.count(complement)) {
//                 return {numMap[complement], i};
//             }
//             numMap[nums[i]] = i;
//         }

//         return {}; // No solution found
//     }
// };