class Solution {
public:
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        unordered_set<int> s(nums.begin(), nums.end());
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* curr = dummy;

        while (curr->next) {
            if (s.count(curr->next->val))
                curr->next = curr->next->next;
            else
                curr = curr->next;
        }
        return dummy->next;
    }
};
