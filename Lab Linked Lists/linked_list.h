#include <iostream>
#include <vector>

struct Node {
  int key;   //data
  Node* next; //next node in data
  Node() = delete; //empty node
  Node(int k, Node* n) : key(k), next(n) {} //shorthand, makes a node
};

// function declarations
void insert(Node*& head, int newKey);
void print(Node* head);
int size(Node* head);
std::vector<int> to_vector(Node* head);
void delete_last_element(Node*& head);
void remove(Node*& head, int oldKey);
void insert_after(Node* head, int oldKey, int newKey);
Node* interleave(Node* list1, Node* list2);
