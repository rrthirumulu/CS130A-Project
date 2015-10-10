template <class T>
class Node
{
public:
  Node(T data) : data(data) {}; // Constructor
  ~Node(); // Destructor
  T getData(); // Returns Data
  Node * next;
  Node * prev;
private:
  T data;
};


template <class T>
T Node<T>::getData()
{
	return data;
}
/*
class LinkedList
{
public:
  LinkedList(); // Constructor
  ~LinkedList(); // Destructor
  void addNode(int x);
  Node* first();
//protected:
//private:
  Node * head;
  Node * tail;
};*/
