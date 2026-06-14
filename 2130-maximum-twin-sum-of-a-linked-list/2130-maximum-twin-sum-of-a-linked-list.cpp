class Solution {
public:
    int pairSum(ListNode* head) {
        // Find middle
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        // slow is now at start of second half — reverse it
        ListNode* prev = nullptr;
        ListNode* curr = slow;
        while (curr) {
            ListNode* nxt = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nxt;
        }
        // Walk first half and reversed second half together
        int ans = 0;
        ListNode* a = head;
        ListNode* b = prev;
        while (b) {
            ans = max(ans, a->val + b->val);
            a = a->next;
            b = b->next;
        }
        return ans;
    }
};