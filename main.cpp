#include "node.h"
#include "linkedlist.h"
#include <iostream>
using namespace std;

int main()
{
//  Node<int> * t = new Node<int>(4); 
//  cout << t->getData() << endl;

  LinkedList<int> * x = new LinkedList<int>();

  x->addNode(2);
  x->addNode(3);
  x->addNode(4);
  cout << x->first()->getData() << endl;
  cout << x->first()->next->getData() << endl;

  x->remove(1);
  cout << x->first()->getData() << endl;
  cout << x->first()->next->getData() << endl;

  delete x;
  return 0;
}
