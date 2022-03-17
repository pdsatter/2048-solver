#include "stack.h"

// STACK FUNCTIONS

int Stack::size(){
  int s = 0;
  node* curr = top;
  while (curr!= nullptr){
    s++;
    curr = curr->next;
  }
  return s;
};

void Stack::push(int d){
  node* newnode = new node(d);
  newnode->next = top;
  top = newnode;
};

int Stack::pop(){
  if (top == nullptr) return 0;
  int d = top->data;
  
  node* temp = top;
  top = top->next;
  delete temp;
  
  return d;
};