
#ifndef _LINKEDLIST_H_
  #include "linkedlist.h"
  #include "user.h"
  #include "node.h"
#endif

class UserNetwork
{
public:
  UserNetwork();
  ~UserNetwork();
  bool addUser(std::string);
  bool addUser(std::string, std::string);
  bool addUser(const User &);
  void deleteUser(std::string);
  std::string write();
  void read(std::string);
  void read();
  void read_friends(std::string);
  void read_friends();
  User & find(std::string);
  bool exists(std::string);
  Node<User> * begin();
  User & get(int);
private:
  List<User> * users;
};
