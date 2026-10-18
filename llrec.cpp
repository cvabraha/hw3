#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************


void llpivot(Node*& head, Node*& smaller, Node*& larger, int pivot){
  if (head == nullptr){
    smaller = nullptr;
    larger = nullptr;
    return;
  }

  Node* rest = head->next;
  if(head->val <= pivot){
    smaller = head;
    head = rest;
    llpivot(head, smaller->next, larger, pivot);
  }else{
    larger = head;
    head = rest;
    llpivot(head, smaller, larger->next, pivot);
  }
}