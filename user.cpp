#include <iostream>
#include <fstream>
#include <sstream>
#include "user.h"

User::User(std::string uname)
{
  username = uname;
  the_wall = new Wall();
  friends = new List<std::string>();
}

User::User(const User & u)
{
  username = u.username;
  password = u.password;
  the_wall = new Wall();
  the_wall->read(u.the_wall->print() );
  friends = new List<std::string>();
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
void User::addPost(std::string p, std::string u) { the_wall->addPost(p,u); }
void User::deletePost(int index)
{
  the_wall->removePost(index);
}
WallPost & User::get_post(int index){
  the_wall->get(index);
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

void User::addFriend(std::string f)
{
  friends->insert(0, f);
}

void User::print_friends()
{
  for(Node<std::string> * tmp = friends->begin(); tmp!=NULL; tmp=tmp->next)
    std::cout << "THIS IS A FRIEND" << tmp->getData() << std::endl;
}

void User::send_friend_request(std::string u)
{
  std::ofstream outfile;
  outfile.open("friend_requests.txt", std::ios_base::app);
  outfile << username << "\n" << u << "\n";
}
