#ifndef _NODE_H_
#define _NODE_H_

template <class T>
class Node
{
public:
  Node(T d); // Constructor
  Node(const T * d);
  ~Node(); // Destructor
  T & getData(); // Returns Data
  Node<T> * next;
  Node<T> * prev;
private:
 T * data;
};

#include "node.tpp"
#endif
