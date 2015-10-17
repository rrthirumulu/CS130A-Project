#include <iostream>
#ifndef WallPost_H
  #include "wallpost.h"
  #include "wall.h"
#endif

class User
{
public:
  User(std::string);
  User(const User&);
  User(std::string, std::string);
  ~User();
  void setUsername(std::string);
  void setPassword(std::string);
  std::string getPassword() const;
  std::string getUsername() const;
  void addPost(WallPost);
  void addPost(std::string);
  void deletePost(int);
  void readIn(std::string);
  std::string write();
private:
  Wall * the_wall;
  std::string username;
  std::string password;
};
