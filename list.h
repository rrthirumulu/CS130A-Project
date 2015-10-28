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
  T & get (int pos) ;
private:
  Node<T> * head;
};


#include "list.tpp"
#endif
