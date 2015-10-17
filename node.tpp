template <class T>
T Node<T>::getData()
{
	    return * data;
}

template <class T>
Node<T>::~Node()
{
	delete data;
}

template <class T>
Node<T>::Node(T d)
{
	    data = new T(d);
}

