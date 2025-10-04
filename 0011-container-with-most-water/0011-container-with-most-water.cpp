class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int maxArea = 0;

        while (left < right) {
            int h, w = right - left;
            
            if (height[left] < height[right]) {
                h = height[left];
                left++;
            } else {
                h = height[right];
                right--;
            }
            
            int area = h * w;
            if (area > maxArea) maxArea = area;
        }

        return maxArea;
    }
};
