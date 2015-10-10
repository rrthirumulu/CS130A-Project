#include <cstddef>
//#include <iostream>
//using namespace std; 

template <class T>
LinkedList<T>::LinkedList()
{
	head = NULL;
	tail = NULL;
}

template <class T>
LinkedList<T>::~LinkedList()
{
  Node<T> * tmp = head;
  while(head != NULL)
  {
    tmp = head;
	head = head->next;
	delete tmp;
  }
  head = tail = NULL;
}

template <class T>
void LinkedList<T>::addNode(T data)
{
  Node<T> * x = new Node<T>(data);

  if( head == NULL )
  {
    head = x;
    tail = x;
  }
  else
  {
    tail->next = x;
    x->prev = tail;
    tail = x;
  }
}

template <class T>
Node<T> * LinkedList<T>::first()
{
  return head;
}

template <class T>
bool LinkedList<T>::remove(int i)
{
  Node<T> * tmp = head;
  for(int x=0; x<i; x++)
  {
    if (tmp == NULL) return false;
	tmp = tmp->next;
  }

  //Handles if it is first element:
  if (tmp == head)
  {
    head = tmp->next;
	head->prev = NULL;
	delete tmp;
	return true;
  }
  
  //Handles if it is the last element:
  if (tmp == tail)
  {
    tail = tmp->prev;
	tail->next = NULL;
	delete tmp;
	return true;
  }

  tmp->prev->next = tmp->next;
  tmp->next->prev = tmp->prev;
  delete tmp;
  return true;
}
