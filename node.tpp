template <class T>
T Node<T>::getData()
{
	    return data;
}

template <class T>
Node<T>::~Node()
{
	data = 0;
}

template <class T>
Node<T>::Node(T d)
{
	    data = d;
}

