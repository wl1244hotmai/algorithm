/**
Given a linked list, remove the nth node from the end of list and return its head.
For example,
   Given linked list: 1->2->3->4->5, and n = 2.

   After removing the second node from the end, the linked list becomes 1->2->3->5.
   */
   /**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode *head1 = dummy,*head2=dummy;
        for(int i = 0;i<n+1;i++){
            head2 = head2->next;
        }
        while(head2){
            head1 = head1->next;
            head2 = head2->next;
        }
        if(head1->next)
            head1->next = head1->next->next;
        else
            delete head1->next;
        return dummy->next;
    }
};