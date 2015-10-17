#include <iostream>
#include <sstream>
#include "wall.h"

Wall::Wall()
{
	the_wall = new LinkedList<WallPost>;
}

Wall::~Wall()
{
  delete the_wall;
}

void Wall::addPost(std::string p)
{
  WallPost wp(p);
  the_wall->addNode(wp);
}

void Wall::addPost(WallPost wp)
{
	the_wall->addNode(wp);
}

bool Wall::removePost(int i)
{
  the_wall->remove(i);
}

void Wall::setUsername(std::string u)
{
  username = u;
}

std::string Wall::getUsername()
{
  return username;
}

std::string Wall::print()
{
  std::string c = "";
  Node<WallPost> * tmp = the_wall->first();
  
  while(tmp != NULL)
  {
//	std::cout << "Address: " << tmp << std::endl;
//	std::cout << tmp->getData().getAllData() << std::endl;
    c.append(tmp->getData().getAllData());
//    c.append("\n");
	tmp=tmp->next;
  }
  return c;
}

void Wall::read(std::string c)
{
  std::istringstream iss(c);
  for(std::string post, user, t;
      std::getline(iss, post), std::getline(iss, user), std::getline(iss,t);
	  )
  {
//	std::cout << "NEW POST: " << post << user << t << std::endl;
    WallPost * x = new WallPost(post, user);
	the_wall->addNode(*x);
  }
}

void Wall::setW(LinkedList<WallPost> * wp)
{
	the_wall = wp;
}
