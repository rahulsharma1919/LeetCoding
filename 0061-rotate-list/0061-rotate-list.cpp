class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || !head->next || k == 0)
            return head;

        int n = 1;
        ListNode* tail = head;
        while (tail->next) {
            tail = tail->next;
            n++;
        }

        k %= n;
        if (k == 0)
            return head;

        ListNode* cur = head;
        for (int i = 0; i < n - k - 1; i++)
            cur = cur->next;

        tail->next = head;
        head = cur->next;
        cur->next = nullptr;

        return head;
    }
};