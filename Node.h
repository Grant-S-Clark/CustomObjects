#ifndef NODE_CLASS
#define NODE_CLASS

template<typename T>
class Node
{
private:
	T data_;
	Node<T>* next_;

public:
	Node() : next_(nullptr) { return; }
	Node(T data) : next_(nullptr), data_(data) { return; }
	~Node() { return; }

	//Pointer returns.
	Node<T>*& next() { return next_; }
	Node<T>* next() const { return next_; }

	//Data returns.
	T& data() { return data_; }
	T data() const { return data_; }
};

#endif
