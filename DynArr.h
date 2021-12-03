//Name: Grant Clark
//Date: November 29th, 2021
//File: DynArr.h

#ifndef DYN_ARR_H
#define DYN_ARR_H

#include <iostream>

class NullAlloc{};
class OutOfRange{};

template<typename T>
class DynArr{
private:
    int size_;
    int capacity_;
    T *x_;

    //Only resize if new size is greater than capacity or
    //less than one third of capacity. Avoids unecessary
    //allocations.
    inline
    bool needs_resize(const int new_size)
    {
        return new_size > capacity_ || new_size < (capacity_ / 3);
    }
public:
    //Default Constructor. (Empty array)
    DynArr<T>() :
        capacity_(0),
        size_(0),
        x_(nullptr)
    {
        return;
    }

    //Constructor with a set starting size.
    DynArr<T>(const int size) :
        capacity_(size * 2),
        size_(size),
        x_(capacity_ != 0 ? new T[capacity_] : nullptr)
    {
        if (x_ == nullptr && capacity_ > 0)
            throw NullAlloc();

        return;
    }

    //Constructor with an array and its size (or how many
    //elements you want to copy from the sent array)
    //Works with static or dynamic arrays.
    DynArr<T>(const int size, const T * const arr) :
        capacity_(size * 2),
        size_(size),
        x_(capacity_ != 0 ? new T[capacity_] : nullptr)
    {
        if (x_ == nullptr && capacity_ > 0)
            throw NullAlloc();

        for (int i = 0; i < size_; ++i)
            *(x_ + i) = *(arr + i);

        return;
    }

    //Constructor using initializer list.
    DynArr<T>(const std::initializer_list<T> & list) :
        capacity_(list.size() * 2),
        size_(list.size()),
        x_(capacity_ != 0 ? new T[capacity_] : nullptr)
    {
        if (x_ == nullptr && capacity_ > 0)
            throw NullAlloc();
        
        for (int i = 0; i < size_; ++i)
            *(x_ + i) = *(list.begin() + i);
        
        return;
    }

    //Copy constructor.
    DynArr<T>(const DynArr<T> & arr) :
        capacity_(arr.capacity()),
        size_(arr.size()),
        x_(capacity_ != 0 ? new T[capacity_] : nullptr)
    {
        if (x_ == nullptr && capacity_ > 0)
            throw NullAlloc();
    
        for (int i = 0; i < size_; ++i)
            *(x_ + i) = arr[i];
    
        return;
    }

    //Deconstructor.
    ~DynArr<T>()
    {
        if (x_ != nullptr)
            delete[] x_;
        return;
    }

    //Resize the array.
    void resize(const int capacity)
    {
        if (needs_resize(capacity))
        {
            T * new_x = (capacity == 0 ? nullptr : new T[capacity * 2]);

            if (capacity != 0 && new_x == nullptr)
                throw NullAlloc();
    
            int loop_size = (capacity < size_ ? capacity : size_);
            for (int i = 0; i < loop_size; ++i)
                *(new_x + i) = *(x_ + i);

            capacity_ = capacity * 2;
            if (x_ != nullptr)
                delete[] x_;
            x_ = new_x;
        }

        size_ = capacity;
    
        return;
    }

    //Print the array with its size and capacity. Only works
    //if the data within the array is compatible with std::cout.
    void print()
    {
        std::cout << "<capacity:" << capacity_ << ", "
                  << "size:" << size_ << ", "
                  << *this << ">\n";
        return;
    }

    /*
      Returns true if both arrays are the same size and
      all values in this object's array are equal to the
      corresponding values in the parameter array.
      Array data must be compatible with the != operator.
    */
    bool operator==(const DynArr<T> & arr) const
    {
        if (this == &arr)
            return true;
        
        if (size_ != arr.size())
            return false;
    
        for (int i = 0; i < size_; ++i)
            if (*(x_ + i) != arr[i])
                return false;
    
        return true;
    }

    //Returns true if either the array sizes do not match or
    //any values in the arrays are not equal.
    //Array data must be compatible with the != operator.
    bool operator!=(const DynArr<T> & arr) const
    {
        return !(*this == arr);
    }

    //Returns true if the amount of members you are allowed
    //to access is zero.
    bool empty() const { return size_ == 0; }

    //Completely clears the array.
    void clear()
    {
        if (x_ != nullptr)
        {
            size_ = 0;
            capacity_ = 0;
            delete[] x_;
            x_ = nullptr;
        }

        return;
    }
    
    //Assignment operator.
    DynArr<T> & operator=(const DynArr<T> & arr)
    {
        if (this != &arr)
        {
            resize(arr.size());
    
            for (int i = 0; i < size_; ++i)
                *(x_ + i) = arr[i];
        }
        
        return *this;
    }

    //Assignment operator using initializer list.
    DynArr<T> & operator=(const std::initializer_list<T> & list)
    {
        resize(list.size());

        for (int i = 0; i < size_; ++i)
            *(x_ + i) = *(list.begin() + i);
        
        return *this;
    }

    //Concatenation
    DynArr<T> & operator+=(const DynArr<T> & arr)
    {
        resize(size_ + arr.size());

        for(int i = 0; i < arr.size(); ++i)
            *(x_ + (size_ - arr.size()) + i) = arr[i];
    
        return *this;
    }

    //Non array altering concatenation
    DynArr<T> operator+(const DynArr<T> & arr) const
    {
        DynArr<T> ret(*this);

        return ret += arr;
    }

    //Insert element into array at given index.
    DynArr<T> & insert(const int index, const T & val)
    {
        if (index < 0 || index > size_)
            throw OutOfRange();

        resize(size_ + 1);

        for (int i = size_ - 2; i >= index; --i)
            *(x_ + i + 1) = *(x_ + i);

        *(x_ + index) = val;

        return *this;
    }

    //Insert element at the beginning of array.
    DynArr<T> & push_front(const T & val) { insert(0, val); return *this; }

    //Insert element at the end of array.
    DynArr<T> & push_back(const T & val) { insert(size_, val); return *this; }

    //Erase an element from array at given index.
    DynArr<T> & erase(const int index)
    {
        if (index < 0 || index >= size_)
            throw OutOfRange();

        for (int i = index; i < size_ - 1; ++i)
            *(x_ + i) = *(x_ + i + 1);
        resize(size_ - 1);

        return *this;
    }

    //Erase the first element in the array.
    DynArr<T> & pop_front() { erase(0); return *this; }

    //Erase the last element in the array.
    DynArr<T> & pop_back() { erase(size_ - 1); return *this; }

    //Erases first element in the array that is equivalent to val.
    DynArr<T> & remove(const T & val)
    {
        for (int i = 0; i < size_; ++i)
            if (*(x_ + i) == val)
            {
                erase(i);
                return *this;
            }
        return *this;
    }

    //Erase all elements in the array that are equivalent to val.
    DynArr<T> & remove_all(const T & val)
    {
        for (int i = 0; i < size_; ++i)
            if (*(x_ + i) == val)
            {
                erase(i);
                --i;
            }
        return *this;
    }

    //Create a sub array from given index to given length. If
    //length is not given, it will go to the end of the array
    //from the given index.
    DynArr<T> subarr(const int index, const int length = -1)
    {
        if (index < 0 || index >= size_)
            throw OutOfRange();
        
        int ret_size = (length < 0 || length > size_ ? size_ - index : length);
        DynArr<T> ret(ret_size);
        
        for (int i = 0; i < ret_size; ++i)
            ret[i] = *(x_ + (index + i));

        return ret;
    }

    //Information accessing (No bounding checks)
    inline T operator[](const int i) const { return *(x_ + i); }
    inline T & operator[](const int i) { return *(x_ + i); }

    //Information accessing (With bounding checks)
    inline T at(const int i) const
    {
        if (i < 0 || i >= size_)
            throw OutOfRange();
        return *(x_ + i);
    }
    inline T & at(const int i)
    {
        if (i < 0 || i >= size_)
            throw OutOfRange();
        return *(x_ + i);
    }
    inline T front() const
    {
        if (!empty())
            return *x_;
        throw OutOfRange();
    }
    inline T & front()
    {
        if (!empty())
            return *x_;
        throw OutOfRange();
    }
    inline T back() const
    {
        if (!empty())
            return *(x_ + (size_ - 1));
        throw OutOfRange();
    }
    inline T & back()
    {
        if (!empty())
            return *(x_ + (size_ - 1));
        throw OutOfRange();
    }

    //Size access
    inline int size() const { return size_; }

    //Capacity access
    inline int capacity() const { return capacity_; }
};

//Printing
template<typename T>
std::ostream & operator<<(std::ostream & cout, const DynArr<T> & arr)
{
    cout << '[';
    for (int i = 0; i < arr.size(); ++i)
        cout << arr[i] << (i != arr.size() - 1 ? "," : "");
    cout << ']';

    return cout;
}

#endif
