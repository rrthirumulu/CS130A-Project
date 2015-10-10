template <class T>
class LinkedList
{
public:
  LinkedList(); // Constructor
  ~LinkedList(); // Destructor
  void addNode(T data); // Add's a node at the end
  bool remove(int i); // Removes the i'th node
  Node<T> * first();
//protected:
private:
  Node<T> * head;
  Node<T> * tail;
};

#include "linkedlist.tpp"
