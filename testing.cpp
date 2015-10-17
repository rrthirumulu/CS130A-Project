#include "node.h"
#include "linkedlist.h"
#include "wallpost.h"
#include "wall.h"
#include "user.h"
#include "usernetwork.h"
#include <iostream>
using namespace std;

int main()
{
//  Node<int> * t = new Node<int>(4); 
//  cout << t->getData() << endl;
  LinkedList<string> * x = new LinkedList<string>();

  x->addNode("2");
  x->addNode("3");
  x->addNode("4");
  cout << x->first()->getData() << endl;
  cout << x->first()->next->getData() << endl;

  x->remove(1);
  cout << x->first()->getData() << endl;
  cout << x->first()->next->getData() << endl;

  delete x;

  WallPost * a = new WallPost("Hello", "Charlie");
  cout << a->getPost() << endl;
  a->updateTime();
  cout << a->getTime();

  WallPost dd("Hello", "Charlie - g");
  Node<WallPost> * wp = new Node<WallPost>(dd);
  //LinkedList<WallPost> * my_wall_posts = new LinkedList<WallPost>();
  //my_wall_posts->addNode(b);

// LinkedList<WallPost> * wall = new LinkedList<WallPost>;
  Wall * my_wall = new Wall;
  my_wall->addPost("Hello!");
  my_wall->addPost(dd);
  cout <<"WALL 1:\n" << my_wall->print() << endl;

  string my_s = my_wall->print();
  Wall * newWall = new Wall;
  newWall->read(my_s);
  cout <<"WALL 2:\n" << newWall->print() << endl;

  User * me = new User("Charlie Getzen", "ASDF");
  me->addPost(*a);
  me->addPost(dd);
  cout << "Output of me->write():\n" << me->write() << endl;

  User * you = new User("You!");
  you->readIn(me->write() );

  cout << "New Output:\n" << you->write() << endl;

  UserNetwork * un = new UserNetwork();
  un->addUser("James Blake");
  un->addUser(*me);
  un->addUser("Zed");
  un->deleteUser("Charlie Getzen");
  cout << un->write() << endl;

  
}
