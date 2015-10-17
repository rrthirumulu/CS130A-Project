
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
  User find(std::string);
private:
  LinkedList<User> * users;
  

};
