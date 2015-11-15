#include <iostream>
#include <sstream>
#include "wall.h"

Wall::Wall()
{
	the_wall = new List<WallPost>;
}

Wall::~Wall()
{
  delete the_wall;
}

void Wall::addPost(std::string p)
{
  WallPost wp(p);
  the_wall->insert(0, wp);
}
void Wall::addPost(std::string p, std::string u)
{
  WallPost wp(p, u);
  the_wall->insert(0, wp);
}
void Wall::addPost(WallPost wp)
{
	the_wall->insert(0, wp);
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
  for(int i=0, j=the_wall->length(); i<j; i++)
//	std::cout << "Address: " << tmp << std::endl;
//	std::cout << tmp->getData().getAllData() << std::endl;
    c.append(the_wall->get(i).getAllData());
//    c.append("\n");
  
  return c;
}

void Wall::read(std::string c)
{
  std::istringstream iss(c);
  for(std::string post, user, t;
      std::getline(iss, post), std::getline(iss, user), std::getline(iss,t);
	  )
  {
    WallPost * x = new WallPost(post, user);
	the_wall->insert(0, *x);
  }
}

void Wall::setW(List<WallPost> * wp)
{
	the_wall = wp;
}

Node<WallPost> * Wall::begin()
{
  return the_wall->begin();
}

WallPost & Wall::get(int index)
{
  return the_wall->get(index);
}
