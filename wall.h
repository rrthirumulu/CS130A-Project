#include <iostream>

#ifndef LinkedList
  #include "node.h"
  #include "wallpost.h"
  #include "linkedlist.h"
#endif

class Wall
{
public:
  Wall(); // Constructor
  ~Wall(); // Destructor
  void addPost(std::string);
  void addPost(WallPost);
  bool removePost(int);
  void setUsername(std::string);
  std::string getUsername();
  std::string print();
  void read(std::string);
  void setW(LinkedList<WallPost> *);
private:
  LinkedList<WallPost> * the_wall;
  std::string username;

};
