#pragma once
struct node{
  int data;
  node* next = nullptr;
  node() = delete;
  node(int d):data(d), next(nullptr){};
  node(int d, node* n): data(d), next(n){};
};


class Stack{
  private:
    node* top = nullptr;
  public:
    node* gettop(){return top;};
    bool isempty(){
      if(top == nullptr) return true;
      else return false;
    };
    int size();
    void push(int d);
    int pop();
    int peek(){
      if (top== nullptr) return 0;
      return top->data;
    }
};