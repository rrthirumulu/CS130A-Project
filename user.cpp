#include <iostream>
#include <sstream>
#include "user.h"

User::User(std::string uname)
{
  username = uname;
  the_wall = new Wall();
}

User::User(const User & u)
{
  username = u.username;
  password = u.password;
  the_wall = new Wall();
  the_wall->read(u.the_wall->print() );
}

User::User(std::string uname, std::string pword)
{
  username = uname;
  password = pword;
  the_wall = new Wall();
}

User::~User()
{
  delete the_wall;
}

void User::setPassword(std::string pword)
{
  password = pword;
}

void User::setUsername(std::string uname)
{
  username = uname;
}

std::string User::getPassword() const { return password; }
std::string User::getUsername() const { return username; }

void User::addPost(WallPost wp) { the_wall->addPost(wp); }
void User::addPost(std::string text) { the_wall->addPost(text); }

void User::deletePost(int index)
{
  the_wall->removePost(index);
}

std::string User::write()
{
  std::string c="";
  c += /*"username:" +*/ username + "\n";
  c += /*"password:" +*/ password + "\n";
  c += /*"the wall:" +*/ the_wall->print();
  return c;
}

void User::readIn(std::string all)
{
	//username
	//password
	//WALL
  std::istringstream iss(all);
  std::getline(iss, username);
  std::getline(iss, password);
  std::string cin;
  for(std::string temp; std::getline(iss, temp); )
    cin += temp + '\n';
  the_wall->read(cin);
}
