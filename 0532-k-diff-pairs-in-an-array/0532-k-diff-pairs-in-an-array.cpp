class Solution {
public:
    int binarySearch(vector<int>& nums, int start, int k){
        int end = nums.size() - 1;
        while(start <= end){
            int mid = start + (end-start)/2;
            if (nums[mid] == k){
                return mid;
            }
            else if (nums[mid] > k) end = mid - 1;
            else start = mid + 1;
        }
        return -1;
    }
    int findPairs(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        set<pair<int,int>>ans;
        
        for(int i=0; i<nums.size(); i++){
            if(binarySearch(nums, i+1, k + nums[i]) != -1){
                ans.insert({nums[i], nums[i] + k});
            }
        }
        return ans.size();
    }
};