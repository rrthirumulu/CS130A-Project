#include <iostream>

#ifndef _LIST_H_
  #include "node.h"
  #include "wallpost.h"
  #include "list.h"
#endif

class Wall
{
public:
  Wall(); // Constructor
  ~Wall(); // Destructor
  void addPost(std::string);
  void addPost(std::string, std::string);
  void addPost(WallPost);
  bool removePost(int);
  void setUsername(std::string);
  std::string getUsername();
  std::string print();
  void read(std::string);
  void setW(List<WallPost> *);
  Node<WallPost> * begin();
  WallPost & get(int);
private:
  List<WallPost> * the_wall;
  std::string username;
};
