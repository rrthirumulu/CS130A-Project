#include "linkedlist.h"
#include <iostream>
using namespace std;

int main()
{
  Node<int> * t = new Node<int>(4); 
  cout << t->getData() << endl;
  return 0;
}
