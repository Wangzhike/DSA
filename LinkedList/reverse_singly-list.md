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
  如下图所示：    
  ![反转](https://github.com/Wangzhike/raw/master/DSA/LinkedList/picture/reverse_singly-list.jpg)

  1. 定位lList的尾节点lLstTail    
    由于m可能为1，即从原链表的头节点开始反转，此时lList为空，需要特别处理。为了避免这种处理，我们引入头哨兵节点guardH，在这种情况下，lList就只含有guardH一个元素。    
  2. 定位mList的最初的头节点mLstOrgHead又记为mLstHead、需要反转的下一个节点mLstNode    
    mList最初的头节点mLstOrgHead，是反转结束后的尾节点；mLstHead一直为头节点；反转开始前mLstHead的后继是第一个需要反转的节点mLstNode。    
	每次反转前，用succ记录mLstNode的后继，将mLstHead置为mLstNode的后继，mLstHead更新为mLstNode，mLstNode更新为succ，进行下一次反转。如此进行，直到反转结束，结束时mLstNode为rList的头节点。    
  3. 定位rList的头节点mLstNode    
    将反转后mList的尾节点mLstOrgHead的后继更新为rList的头节点mLstNode，将lList尾节点lLstTail的后继更新为反转后mList的头节点mLstHead。反转完成。    


