#include <iostream>
template <class T>
List<T>::List()
{
  head = NULL;
}

template <class T>
List<T>::~List()
{
  Node<T> * tmp = head;
  while(head != NULL)
  {
    tmp = head;
    head = head->next;
    delete tmp;
  }
}

template <class T>
void List<T>::insert(int pos, const T & item)
{
  Node<T> * tmp = head;
  Node<T> * x = new Node<T>(&item);

  if(pos == 0 || head == NULL)
  {
    x->next = head;
    head = x;
    return;
  }

  for( ; pos > 1; pos--)
    if(tmp->next != NULL) tmp=tmp->next;
  x->next = tmp->next;
  tmp->next = x;
}

template <class T>
void List<T>::remove(int pos)
{
  Node<T> * tmp = head;
  Node<T> * to_delete;
  
  if (head == NULL) return;
  if (pos <= 0)
  {
    to_delete = head;
    head = head->next;
    delete to_delete;
    return;
  }

  // For any pos > 0, set tmp to be the position before:
  for( ; pos > 1; pos--) if (tmp!=NULL) tmp = tmp->next;
  
  if(tmp->next == NULL) return;
  to_delete = tmp->next;
  tmp->next = to_delete->next;
  delete to_delete;

}


template <class T>
void List<T>::set(int pos, const T & item)
{
  remove(pos);
  insert(pos, item);
}
template <class T>
T & List<T>::get(int pos) 
{
  T * x = new T;
  Node<T> * tmp = head;
  for( ; pos > 0; pos--)
    if (tmp != NULL) tmp = tmp->next;
  if (tmp == NULL) return * x;
  return (tmp->getData());
  
}
