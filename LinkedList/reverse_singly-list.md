# 单链表反转    

## 描述    
  将单链表位置m到n(从1开始编号)的节点进行反转，要求常量空间和常量时间。    

## 解法    
  根据要反转的子链表，可以将该链表分为3个部分：lList, mList, rList。    
  1. lList    
    lList的尾节点的`next`节点(即lList的尾后节点)是要进行反转的子链表的第一个节点m。    
  2. mList    
    mList是要进行反转的子链表，即节点m到n。    
  3. rList    
    rList的头节点是需要反转的子链表mList的尾节点的`next`节点(即mList的尾后元素)，一直到该链表结束。    

  反转步骤：     
  1. 定位lList的尾节点lLstTail    
    由于m可能为1，即从原链表的头节点开始反转，此时lList为空，需要特别处理。为了避免这种处理，我们引入头哨兵节点guardH，在这种情况下，lList就只含有guardH一个元素。    
  2. 定位mList的最初的头节点mLstOrgHead又记为mLstHead、需要反转的下一个节点mLstNode    
    mList最初的头节点mLstOrgHead，是反转结束后的尾节点；mLstHead一直为头节点；反转开始前mLstHead的后继是第一个需要反转的节点mLstNode。    
	每次反转前，用succ记录mLstNode的后继，将mLstHead置为mLstNode的后继，mLstHead更新为mLstNode，mLstNode更新为succ，进行下一次反转。如此进行，直到反转结束，结束时mLstNode为rList的头节点。    
  3. 定位rList的头节点mLstNode    
    将反转后mList的尾节点mLstOrgHead的后继更新为rList的头节点mLstNode，将lList尾节点lLstTail的后继更新为反转后mList的头节点mLstHead。反转完成。    
  如下图所示：    
  ![反转](https://github.com/Wangzhike//DSA/raw/master/LinkedList/picture/reverse_singly-list.jpg)

## 刷题    
  1. [LeetCode 234. Palindrome Linked List](https://leetcode.com/problems/palindrome-linked-list/description/)    
  题目描述：    
  > Given a singly linked list, determine if it is a palindrome.    

  先定位到单链表的中点，然后对后面的子链表进行反转，反转后比较前后子链表是否相等即可。    
  ```cpp
    bool isPalindrome(ListNode* head) {
        int len = 0;
        for (auto p = head; p; p = p->next)
            ++len;
        if (len <= 1)
            return true;
        ListNode guardH(-1);
        guardH.next = head;
        auto lLstTail = &guardH;
        for (int i = 0; i < len/2; ++i)
            lLstTail = lLstTail->next;
        if (len & 0x1)
            lLstTail = lLstTail->next;
        auto mLstOrgHead = lLstTail->next;
        auto mLstHead = lLstTail->next;
        auto mLstNode = mLstHead->next;
        while (mLstNode) {
            auto succ = mLstNode->next;
            mLstNode->next = mLstHead;
            mLstHead = mLstNode;
            mLstNode = succ;
        }
        mLstOrgHead->next = mLstNode;
        lLstTail->next = mLstHead;
        for (auto lLstp = guardH.next, mLstp = mLstHead; mLstp; mLstp = mLstp->next, lLstp = lLstp->next) {
            // cout << lLstp->val << ", " << mLstp->val << endl;
            if (lLstp->val != mLstp->val)
                return false;
        }
        return true;
  ```

  2. [LeetCode 206. Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/description/)    
    题目描述：    
	> Reverse a singly linked list.    

	```cpp
    ListNode* reverseList(ListNode* head) {
        if (head == NULL)
            return head;
        auto newHead = head;
        auto p = head->next;
        head->next = NULL;
        while (p) {
            auto succ = p->next;
            p->next = newHead;
            newHead = p;
            p = succ;
        }
        return newHead;
    } 
	```

  3. [LeetCode 92. Reverse Linked List II](https://leetcode.com/problems/reverse-linked-list-ii/description/)    
    题目描述：    
	
	> Reverse a linked list from position m to n. Do it in-place and in one-pass.    
	  For example:    
	  Given 1->2->3->4->5->NULL, m = 2 and n = 4,    
	  return 1->4->3->2->5->NULL.    
	
	```cpp
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if (n - m == 0)
            return head;
        ListNode hguard(-1);
        hguard.next = head;
        ListNode* lTail = &hguard;
        for (int i = 0; i < m - 1; ++i)
            lTail = lTail->next;
        // cout << lTail->val << endl;
        ListNode* mHead = lTail->next;
        ListNode* pHead = mHead, *p = mHead->next;
        for (int i = 0; i < n - m; ++i) {
            ListNode* succ = p->next;
            p->next = pHead;
            pHead = p;
            p = succ;
        }
        // if (p)
        //     cout << p->val << endl;
        // else
        //     cout << "NULL" << endl;
        lTail->next = pHead;
        mHead->next = p;
        return hguard.next;
    } 
	```    


