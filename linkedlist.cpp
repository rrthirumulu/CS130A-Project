#include "linkedlist.h"
#include <iostream>
using namespace std;

template <class T>
Node<T>::~Node()
{
	data = NULL;
}
/*
template <class T>
T Node<T>::getData()
{
	return data;
}
*/


/*



LinkedList::LinkedList(void)
{	
 head = NULL;
 tail = NULL;
}

LinkedList::~LinkedList()
{
  Node * tmp;
  while (head)
  {
    tmp = head;
	head = head->next;
	delete tmp;
  }
  head = tail = NULL;
}

void LinkedList::addNode(int x)
{
  Node * t = new Node(x);
  Node * tmp = head;
  if(tmp == NULL)
  {
    head = tail = t;
  }
  else
  {
    while(tmp->next != NULL) { tmp = tmp->next; }
	tmp->next = t;
	t->prev = tail;
	tail = t;
  }
}

Node* LinkedList::first()
{
  return head;
}*/
