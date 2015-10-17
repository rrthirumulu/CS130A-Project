#include <iostream>
#include <sstream>
#include <fstream>
#include "usernetwork.h"

UserNetwork::UserNetwork()
{
  users = new LinkedList<User>();
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

  for(Node<User> * tmp = users->first();  tmp != NULL; tmp=tmp->next)
  {
    if (tmp->getData().getUsername() == name)
      return false;
  }

  User * u = new User(name, pword);
  users->addNode(*u);
  delete u;
  return true;
}
bool UserNetwork::addUser(const User & u)
{
  for(Node<User> * tmp = users->first(); tmp != NULL; tmp=tmp->next)
    if (tmp->getData().getUsername() == u.getUsername() ) 
      return false;

  users->addNode(u);
  return true;
}
void UserNetwork::deleteUser(std::string name)
{
  int i = 0;
  for(Node<User> * tmp = users->first(); ; tmp = tmp->next)
      {
		if (tmp == NULL) return;
		if (tmp->getData().getUsername() == name) break;
	    i++;
      }
  std::cout << i << std::endl;
  users->remove(i);
}

std::string UserNetwork::write()
{
  std::string output = "";
  for(Node<User> * tmp = users->first(); tmp != NULL; tmp=tmp->next )
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

User UserNetwork::find(std::string uname)
{
  Node<User> *tmp = users->first();
  for( ; tmp != NULL; tmp=tmp->next)
    if (tmp->getData().getUsername() == uname )
      return tmp->getData() ;
  User x("NO");
  return x;
}
