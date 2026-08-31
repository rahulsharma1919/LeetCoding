/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int firstIdx = -1, lastIdx = -1, minGap = INT_MAX;

        ListNode* prev = head;
        ListNode* cur = head->next;
        int idx = 1;

        while (cur->next != nullptr) {
            bool isMax = cur->val > prev->val && cur->val > cur->next->val;
            bool isMin = cur->val < prev->val && cur->val < cur->next->val;

            if (isMax || isMin) {
                if (firstIdx == -1) {
                    firstIdx = idx;
                } else {
                    minGap = min(minGap, idx - lastIdx);
                }
                lastIdx = idx;
            }

            prev = cur;
            cur = cur->next;
            idx++;
        }

        if (firstIdx == -1 || firstIdx == lastIdx) {
            return {-1, -1};
        }

        int maxDistance = lastIdx - firstIdx;
        return {minGap, maxDistance};
    }
};