#include <cmath>

//singly-linked list
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

//707. Design Linked List
class MyLinkedList {
public:
  struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
  MyLinkedList() : _size(0), _dummy_head(new ListNode()) {}

  int get(int index) {
    if (index > _size - 1 || index < 0) return -1;
    ListNode* curr = _dummy_head->next;
    while(index--) {
      curr = curr -> next;
    }
    return curr->val;
  }

  void addAtHead(int val) {
    ListNode* head = new ListNode(val, _dummy_head->next);
    _dummy_head->next = head;
    ++_size;
  }

  void addAtTail(int val) {
    ListNode* tail = new ListNode(val);
    ListNode* curr = _dummy_head;
    while(curr->next != nullptr) {
      curr = curr->next;
    }
    curr->next = tail;
    ++_size;
  }

  void addAtIndex(int index, int val) {
    if (index > _size || index < 0) return;
    ListNode* curr = _dummy_head;
    while (index--) {
      curr = curr->next;
    }
    ListNode* insert = new ListNode(val, curr->next);
    curr->next = insert;
    ++_size;
  }

  void deleteAtIndex(int index) {
    if (index > _size - 1 || index < 0) return;
    ListNode* curr = _dummy_head;
    while (index--) {
      curr = curr->next;
    }
    ListNode* tmp = curr->next;
    curr->next = curr->next->next;
    delete tmp;
    --_size;
  }

private:
  int _size;
  ListNode* _dummy_head;
};

//203. Remove Linked List Elements
ListNode* removeElements(ListNode* head, int val) {
  ListNode* dummy_head = new ListNode(0, head);
  for (ListNode* curr = dummy_head; curr->next != nullptr;) {
    if (curr->next->val == val) {
      ListNode* tmp = curr->next;
      curr->next = curr->next->next;
      delete tmp;
    } else {
      curr = curr->next;
    }
  }
  head = dummy_head->next;
  delete dummy_head;
  return head;
}

//206. Reverse Linked List
ListNode* reverseList(ListNode* head) {
  ListNode* curr = head;
  ListNode* pre = nullptr;
  while(curr != nullptr) {
    ListNode* tmp = curr;
    curr = curr->next;
    tmp->next = pre;
    pre = tmp;
  }
  return pre;
}

//24. Swap Nodes in Pairs
ListNode* swapPairs(ListNode* head) {
  ListNode* _dummy_head = new ListNode(0, head);
  ListNode* curr = _dummy_head;
  while(curr->next && curr->next->next != nullptr) {
    ListNode* tmp1 = curr->next;
    ListNode* tmp3 = curr->next->next->next;
    
    curr->next = curr->next->next;
    curr->next->next = tmp1;
    tmp1->next = tmp3;
    curr = curr->next->next;
  }

  ListNode* new_head = _dummy_head->next;
  delete _dummy_head;
  return new_head;
}

//19. Remove Nth Node From End of List
ListNode* removeNthFromEnd(ListNode* head, int n) {
  ListNode* _dummy_head = new ListNode(0, head);
  ListNode* curr = _dummy_head;
  ListNode* pre = _dummy_head;

  for (int i = 0; i < n; ++i) {
    curr = curr->next;
  }
  
  while(curr->next != nullptr) {
    curr = curr->next;
    pre = pre->next;
  }

  ListNode* tmp = pre->next;
  pre->next = pre->next->next;
  delete tmp;

  ListNode* new_head = _dummy_head->next;
  delete _dummy_head;
  return new_head;
}

//160. Intersection of Two Linked Lists
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
  int lenA = 0;
  int lenB = 0;

  for (ListNode* currA = headA; currA != nullptr; currA = currA->next, ++lenA) {}
  for (ListNode* currB = headB; currB != nullptr; currB = currB->next, ++lenB) {}
  
  ListNode *currL, *currS;
  if (lenA > lenB) {
    currL = headA;
    currS = headB;
  } else {
    currL = headB;
    currS = headA;
  }

  for (int i = 0; i < abs(lenA - lenB); ++i) {
    currL = currL->next;
  }

  while (currL != nullptr) {
    if (currL == currS) return currL;
    currL = currL->next;
    currS = currS->next; 
  }

  return nullptr;
}

//141. Linked List Cycle
bool hasCycle(ListNode* head) {
  ListNode* fast = head;
  ListNode* slow = head;

  while (fast != nullptr && fast->next != nullptr) {
    fast = fast->next->next;
    slow = slow->next;
    if (fast == slow) {
      return true;
    }
  }
  return false;
}

//142. Linked List Cycle II
ListNode* detectCycle(ListNode* head) {
  ListNode* fast = head;
  ListNode* slow = head;

  while (fast != nullptr && fast->next != nullptr) {
    fast = fast->next->next;
    slow = slow->next;
    if (slow == fast) {
      ListNode* index1 = fast;
      ListNode* index2 = head;
      while (index1 != index2) {
        index1 = index1->next;
        index2 = index2->next;
      }
      return index2;
    }
  }
  return nullptr;
}
