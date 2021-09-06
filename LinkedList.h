#ifndef LINKED_LIST_CLASS
#define LINKED_LIST_CLASS

#include <iostream>
#include "Node.h"

template<typename T>
class LinkedList
{
private:
	//Pointer to first node in the dataset.
	Node<T>* x_;

	//Error throwing.
	inline void error(const char* c) const
	{
		std::cout << "ERROR: " << c << '\n';
		throw std::exception();
	}
public:
	//Empty LinkedList.
	LinkedList() : x_(nullptr) { return; }


	//LinkedList with a certain amount of nodes allocated.
	LinkedList(const unsigned int size) : x_(nullptr)
	{
		Node<T>* node;
		for (int i = 0; i < size; i++)
		{
			//Create the first node.
			if (x_ == nullptr)
			{
				x_ = new Node<T>;
				if (x_ == nullptr)
					error("A memory allocation has failed (returned nullptr).");
			}
				
			else
			{
				node = x_;

				//Find next open space for a node.
				while (node->next() != nullptr)
					node = node->next();

				node->next() = new Node<T>;
				if (node->next() == nullptr)
					error("A memory allocation has failed (returned nullptr).");
			}
		}

		return;
	}


	//LinkedList copy constructor.
	LinkedList(const LinkedList<T>& list)
	{
		if (list.empty())
			x_ = nullptr;
		else
		{
			Node<T>* node;
			for (int i = 0; i < list.size(); i++)
			{
				//Create the first node.
				if (x_ == nullptr)
				{
					x_ = new Node<T>(list[i]);
					if (x_ == nullptr)
						error("A memory allocation has failed (returned nullptr).");
				}

				else
				{
					node = x_;

					//Find next open space for a node.
					while (node->next() != nullptr)
						node = node->next();

					node->next() = new Node<T>(list[i]);
					if (node->next() == nullptr)
						error("A memory allocation has failed (returned nullptr).");
				}
			}
		}

		return;
	}


	~LinkedList()
	{
		clear();
		return;
	}


	//Returns the number of nodes in the LinkedList.
	unsigned int size() const
	{
		unsigned int i = 0;
		Node<T>* node = x_;

		while (node != nullptr)
		{
			node = node->next();
			i++;
		}

		return i;
	}


	//Returns true if the LinkedList has no nodes.
	bool empty() const
	{
		if (x_ == nullptr)
			return true;
		return false;
	}


	//Return data at a specific index as a reference.
	T& operator[](const unsigned int index)
	{
		//Will throw an error if the index is out of bounds or
		//the LinkedList is empty.
		if (x_ == nullptr || size() - 1 < index)
			error("Operator[] invalid index.");

		Node<T>* node = x_;
		for (int i = 0; i < index; i++)
			node = node->next();

		return node->data();
	}


	//Return data at a specific index as a constant.
	T operator[](const unsigned int index) const
	{
		//Will throw an error if the index is out of bounds or
		//the LinkedList is empty.
		if (x_ == nullptr || size() - 1 < index)
			error("Operator[] invalid index.");

		Node<T>* node = x_;
		for (int i = 0; i < index; i++)
			node = node->next();

		return node->data();
	}


	//Appends a new node onto the end of the LinkedList and gives
	//it the data value used as a parameter.
	LinkedList<T>& push_back(T data)
	{
		if (x_ == nullptr)
		{
			x_ = new Node<T>;
			if (x_ == nullptr)
				error("A memory allocation has failed (returned nullptr).");
			x_->data() = data;
		}

		else
		{
			Node<T>* node = x_;
			while (node->next() != nullptr)
				node = node->next();
			node->next() = new Node<T>;
			node->next()->data() = data;
		}

		return *this;
	}


	//Erase the node at the end of the LinkedList.
	LinkedList<T>& pop_back()
	{
		if (x_ == nullptr)
			error("Cannot pop_back() an empty LinkedList.");
		
		//If there is only one node.
		if (x_->next() == nullptr)
		{
			delete x_;
			x_ = nullptr;
		}
		
		else
		{
			Node<T>* node = x_;

			//Find the last node in the list.
			while (node->next()->next() != nullptr)
				node = node->next();

			delete node->next();
			node->next() = nullptr;
		}

		return *this;
	}

	
	//Deletes all nodes in the LinkedList.
	LinkedList<T>& clear()
	{
		Node<T> *node = x_, *erasedNode = nullptr;

		while (node != nullptr)
		{
			erasedNode = node;
			node = node->next();
			delete erasedNode;
		}

		x_ = nullptr;

		return *this;
	}


	//Erase a single piece of data from the LinkedList at a given index.
	LinkedList<T>& remove(const unsigned int index)
	{
		if (x_ == nullptr || size() - 1 < index)
			error("erase() invalid index.");

		//If it is erasing the last value, just perform a pop_back().
		if (index == size() - 1)
		{
			pop_back();
			return *this;
		}

		else
		{
			Node<T>* node = x_;

			//If deleting the first node in the LinkedList.
			if (index == 0)
			{
				x_ = x_->next();
				delete node;
			}

			else
			{
				Node<T> *erasedNode = nullptr, *previousNode = nullptr;
				for (int i = 0; i < size(); i++)
				{
					if (i == index)
					{
						erasedNode = node;
						node = node->next();
						previousNode->next() = node;
					}
					else
					{
						previousNode = node;
						node = node->next();
					}
				}

				delete erasedNode;
			}

			return *this;
		}
	}


	//Will remove a given amount of nodes from the LinkedList starting from a given
	//index and going down the list.
	LinkedList<T>& remove(const unsigned int index, const unsigned int amount)
	{
		if (x_ == nullptr || size() - 1 < index)
			error("erase() invalid index.");
		if (index + amount > size())
			error("erase() invalid amount.");

		//If you are only erasing one node.
		if (amount == 1)
		{
			remove(index);
			return *this;
		}

		else
		{
			Node<T>* node = x_;

			//If starting at the first node.
			if (index == 0)
			{
				for (int i = 0; i < amount; i++)
				{
					node = node->next();
					delete x_;
					x_ = node;
				}
			}

			else
			{
				Node<T> *erasedNode = nullptr, *saveNode = nullptr;
				for (int i = 0; i < size(); i++)
				{
					if (i == index)
					{
						for (int j = 0; j < amount; j++)
						{
							node = node->next();
							i++;
						}

						erasedNode = saveNode->next();
						saveNode->next() = node;

						for (int j = 0; j < amount; j++)
						{
							saveNode = erasedNode->next();
							delete erasedNode;
							erasedNode = saveNode;
						}
					}

					else
					{
						saveNode = node;
						node = node->next();
					}
				}
			}

			return *this;
		}
	}


	//Will insert a node with specific data at a given index.
	LinkedList<T>& insert(const unsigned int index, const T data)
	{
		if (x_ == nullptr || size() - 1 < index)
			error("insert() invalid index.");

		if (index == 0)
		{
			Node<T>* node = x_;
			x_ = new Node<T>(data);
			x_->next() = node;
		}

		else if (index == size())
			push_back(data);

		else
		{
			Node<T> *node = x_, *previousNode = nullptr;
			for (int i = 0; i < index; i++)
			{
				previousNode = node;
				node = node->next();
			}

			previousNode->next() = new Node<T>(data);
			previousNode->next()->next() = node;
		}

		return *this;
	}


	//Copy function. Copies the size and values of an r-value LinkedList
	//into the l-value LinkedList.
	void operator=(const LinkedList<T>& list)
	{
		if (this != &list)
		{
			clear();

			if (!list.empty())
			{
				x_ = new Node<T>(list[0]);

				Node<T>* node;
				for (int i = 0; i < list.size() - 1; i++)
				{
					node = x_;
					while (node->next() != nullptr)
						node = node->next();
					node->next() = new Node<T>(list[i + 1]);
				}
			}
		}

		return;
	}


	//Defenitions of these functions are found outside of its scope.
	template<typename T2> friend
		std::ostream& operator<<(std::ostream&, const LinkedList<T2>&);
	template <typename T2> friend
		std::istream& operator>>(std::istream&, LinkedList<T2>&);
};

//Prints out the values stored in the LinkedList.
template<typename T>
std::ostream& operator<<(std::ostream& out, const LinkedList<T>& list)
{
	Node<T>* node = list.x_;

	out << '[';
	while (node != nullptr)
	{
		out << node->data();
		node = node->next();

		if (node != nullptr)
			out << ", ";
	}
	out << ']';

	return out;
}

//Takes an input unsigned integer and allows the user to append
//that many values into the LinkedList.
template<typename T>
std::istream& operator>>(std::istream& in, LinkedList<T>& list)
{
	unsigned int total;
	std::cout << "Input the amount of values: ";
	in >> total;

	T data;
	for (int i = 0; i < total; i++)
	{
		in >> data;
		list.push_back(data);
	}

	return in;
}

#endif