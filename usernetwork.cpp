#include <iostream>
#include <sstream>
#include <fstream>
#include "usernetwork.h"

UserNetwork::UserNetwork()
{
  users = new List<User>();
}

UserNetwork::~UserNetwork()
{
  delete users;
}

bool UserNetwork::addUser(std::string name)
{
  return addUser(name, "password");
}

bool UserNetwork::addUser(std::string name, std::string pword)
{

  for(Node<User> * tmp = users->begin();  tmp != NULL; tmp=tmp->next)
  {
    if (tmp->getData().getUsername() == name)
      return false;
  }

  User * u = new User(name, pword);
  users->insert(0, *u);
  delete u;
  return true;
}
bool UserNetwork::addUser(const User & u)
{
  for(Node<User> * tmp = users->begin(); tmp != NULL; tmp=tmp->next)
    if (tmp->getData().getUsername() == u.getUsername() ) 
      return false;

  users->insert(0, u);
  return true;
}
void UserNetwork::deleteUser(std::string name)
{
  int i = 0;
  for(Node<User> * tmp = users->begin(); ; tmp = tmp->next)
      {
		if (tmp == NULL) return;
		if (tmp->getData().getUsername() == name) break;
	    i++;
      }
  users->remove(i);
}

std::string UserNetwork::write()
{
  std::string output = "";
  for(Node<User> * tmp = users->begin(); tmp != NULL; tmp=tmp->next )
  {
    output += tmp->getData().write() + "\n\n";
  }

  std::ofstream out("data.txt");
  out << output;
  out.close();

  return output;
}

void UserNetwork::read(std::string c)
{
  std::string a_user="";
  std::istringstream iss(c);
  
  for(std::string temp=""; std::getline(iss, temp); )
  {
    if (temp[0] == 0)
    {
      if (a_user != "")
	  {
		  User * x = new User("temp name");
		  x->readIn(a_user);
		  addUser(*x);
		  delete x;
	  }
	  a_user = "";
	}
	else
       a_user += temp + "\n";
  }
}

void UserNetwork::read_friends(std::string c)
{
  Node<User> * u1;
  Node<User> * u2;
  std::istringstream iss(c);
  for(std::string p1, p2; std::getline(iss, p1), std::getline(iss, p2); )
  {
    for(u1 = users->begin(); ; u1=u1->next)
      if (p1 == u1->getData().getUsername()) break;
    for(u2 = users->begin(); ; u2 = u2->next)
      if(p2 == u2->getData().getUsername()) break;
    u1->getData().addFriend(p2);
    u2->getData().addFriend(p1);
  }
}

void UserNetwork::read()
{
  std::ifstream myfile("data.txt");
  std::string line;
  std::string complete = "";
  if (myfile.is_open())
  {
    while( std::getline(myfile, line) )
      complete += line + "\n";
	myfile.close();
  }

  read(complete);
}

void UserNetwork::read_friends()
{
  std::ifstream myfile("data_friends.txt");
  std::string line, complete="";
  if (myfile.is_open())
  {
    while(std::getline(myfile, line) )
      complete += line + "\n";
    myfile.close();
  }
  read_friends(complete);
}

User & UserNetwork::find(std::string uname)
{
  Node<User> *tmp = users->begin();
  for( ; tmp != NULL; tmp=tmp->next)
    if (tmp->getData().getUsername() == uname )
      return tmp->getData() ;
  //User x("NO");
  //return x;
}

Node<User> * UserNetwork::begin()
{
  return users->begin();
}
User & UserNetwork::get(int index)
{
  return users->get(index);
}
