template <class T>
class Node
{
public:
  Node(T data); // Constructor
  ~Node(); // Destructor
  T getData(); // Returns Data
  Node * next;
  Node * prev;
private:
  T data;
};

#include "node.tpp"
