#ifndef _LIST_H_
#define _LIST_H_

#ifndef _NODE_H_
  #include "node.h"
#endif

template <class T>
class List {
public:
  List();
  ~List();
  void insert (int pos, const T & item);
  void remove (int pos);
  void set (int pos, const T & item);
  T & get (int pos);
  int length();
  Node<T> * begin();

private:
  Node<T> * head;
  int len;
};


#include "list.tpp"
#endif
