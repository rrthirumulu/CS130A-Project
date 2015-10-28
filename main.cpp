#include "node.h"
#include "linkedlist.h"
#include "wallpost.h"
#include "wall.h"
#include "user.h"
#include "usernetwork.h"
#include "list.h"
#include <iostream>
using namespace std;

int main()
{
  List<int> * x = new List<int>();
  x->insert(0, 4); // 4
  x->insert(1, 5); // 4 5
  x->insert(1, 3); // 4 3 5
  x->remove(1); // 4 5
  x->set(1, 6); // 4 6
  cout << x->get(2) << endl;
}
    
