#ifndef DYN_ARR
#define DYN_ARR

#include <iostream>

template <typename T>
class DynArr{
private:
    //Pointer to array of data.
    T* x_;
    unsigned int size_;
    unsigned int capacity_;

    //Returns true if the new size is either greater than current capacity or
    //if it is less than or equal to one third of the current capacity.
    inline bool needs_resize(const int size) const
    {
        return (capacity_ < size || (capacity_ / 3) >= size);
    }
    
    //Exception throwing function.
    inline void throw_exception(const char* const message) const
    {
        std::cout << "\nERROR: " << message << '\n';
        throw std::exception();
    }
    
public:
    DynArr() :
        x_(nullptr), size_(0), capacity_(0) {return;};
        
    //Constructor that allocates a certain amount of room for data.
    DynArr(int size) :
        size_(size), capacity_(size)
    {
        //0 = empty.
        if (capacity_ == 0)
            x_ = nullptr;
        else
        {
            //Allocate space.
            x_ = new T[capacity_];

            //Allocation failed.
            if (x_ == nullptr)
                throw_exception("memory allocation returns NULL.");
        }

        return;
    }


    //Constructor that can be used to initialize a DynArr using
    //a list of elements that match the datatype of the DynArr.
    DynArr(std::initializer_list<T> l) :
        size_(l.size()), capacity_(l.size())
    {
        //0 = emtpy.
        if (capacity_ == 0)
            x_ = nullptr;
        else
        {
            //Allocate space.
            x_ = new T[capacity_];

            //Allocation failed.
            if (x_ == nullptr)
                throw_exception("memory allocation returns NULL.");

            //Copy data.
            for (int i = 0; i < size_; i++)
                *(x_ + i) = *(l.begin() + i);
        }

        return;
    }


    //Constructor that takes a given array and its size and makes
    //it have the same size and data.
    DynArr(int size, T a[]) :
        size_(size), capacity_(size)
    {
        //0 = empty.
        if (capacity_ == 0)
            x_ = nullptr;
        else
        {
            //Allocate space.
            x_ = new T[capacity_];

            //Allocation failed.
            if (x_ == nullptr)
                throw_exception("memory allocation returns NULL.");

            //Copy data.
            for (int i = 0; i < size_; i++)
                *(x_ + i) = a[i];
        }

        return;
    }


    //Given a DynArr, allocate its same capacity and set the same size value,
    //then set the same values into the DynArr.
    DynArr(const DynArr<T> & a)
    {
        //Copy values.
        size_ = a.size();
        capacity_ = a.capacity();
    
        //If it was empty.
        if (a.capacity() == 0)
            x_ = nullptr;

        else
        {
            //Allocate space.
            x_ = new T[capacity_];
            //Allocation failed.
            if (x_ == nullptr)
                throw_exception("memory allocation returns NULL.");

            //Copy data.
            for (int i = 0; i < size_; i++)
                *(x_ + i) = a[i];
        }

        return;
    }


    ~DynArr()
    {
        //If not empty, free the taken space.
        if(x_ != nullptr)
            delete[] x_;

        return;
    }


    //Return values.
    unsigned int size() const { return size_; }
    unsigned int capacity() const { return capacity_; }


    //Return data at the given index as a reference.
    T& operator[](const int index)
    {
        //Out of bounds.
        if (index >= size_ || index < 0)
            throw_exception("invalid index called within operator[]().");
        
        return *(x_ + index);
    }


    //Return data at the given index as a constant.
    T operator[](const int index) const
    {
        //Out of bounds.
        if (index >= size_ || index < 0)
            throw_exception("invalid index called within operator[]().");
        
        return *(x_ + index);
    }
    

    //Compares the sizes and data points of two DynArr objects.
    //Returns true if they match.
    bool operator==(const DynArr<T>& a) const
    {
        //If it is the same object.
        if (this == &a)
            return true;
        //If the sizes are not equal.
        else if (size_ != a.size())
            return false;
        else
        {
            //Compare values.
            for (int i = 0; i < size_; i++)
                if (*(x_ + i) != a[i])
                    return false;
        }

        return true;
    }


    //Returns opposite of opreator==().
    bool operator!=(const DynArr<T>& a) const
    {
        return !(*this == a);
    }


    //Copies the size, capacity, and values of a r-value DynArr
    //into the l-value DynArr.
    DynArr<T>& operator=(const DynArr<T>& a)
    {
        if (this != &a)
        {
            size_ = a.size();
            capacity_ = a.capacity();

            //Allocate space.
            T* x = new T[capacity_];
            //Allocation fauiled.
            if (x == nullptr)
                throw_exception("memory allocation returns NULL.");

            //Copy values.
            for (int i = 0; i < size; i++)
                *(x + i) = a[i];

            delete x_;
            x_ = x;
        }

        return *this;
    }


    //Copies the size and values of an array that the DynArr is
    //being set to be equal to.
    DynArr<T>& operator=(std::initializer_list<T> l)
    {
        //Resize
        if (needs_resize(l.size()))
            resize(l.size());

        //Set values
        for (int i = 0; i < l.size(); i++)
            *(x_ + i) = *(l.begin() + i);

        //Set appropriate size.
        size_ = l.size();

        return *this;
    }


    //Append values of a given DynArr into the subject DynArr.
    DynArr<T>& operator+=(const DynArr<T>& a)
    {
        //Resize.
        if (needs_resize(size_ + a.size()))
            resize(size_ + a.size());

        //Copy values.
        for (int i = 0; i < a.size(); i++)
            *(x_ + (size_ + i)) = a[i];
        
        //Set appropriate size.
        size += a.size();

        return *this;
    }


    //Creates and returns a DynArr built with the l-value DynArr
    //values in front and the r-value  DynArr values in the back.
    DynArr<T> operator+(const DynArr<T>& a)
    {
        //Make new DynArr.
        DynArr<T> new_a(size + a.get_size());

        //Copy values.
        for (int i = 0; i < size_; i++)
            new_a[i] = *(x_ + i);
        for (int i = 0; i < a.size(); i++)
            new_a[size_ + i] = a[i];

        return new_a;
    }

    //Defenitions for these functions are found below the class.
    template<typename T2> friend
    std::ostream& operator<<(std::ostream&, const DynArr<T2>);
    template<typename T2> friend
    std::istream& operator>>(std::istream&, DynArr<T2>&);
    

    //Insert a piece of data into a given data point.
    DynArr<T>& insert(const int index, const T val)
    {
        //Out of bounds.
        if (index > size_ || index < -1)
            throw_exception("invalid index called within insert().");
    
        //Resize.
        if (needs_resize(size_ + 1))
            resize(size_ + 1);
    
        //Open a space for the new value.
        for (int i = size_; i > index; i--)
            *(x_ + i) = *(x_ + (i - 1));

        //Insert value.
        *(x_ + index) = val;

        size_++;
        
        return *this;
    }


    //Removes a value at a given index from the DynArr.
    DynArr<T>& remove(const int index)
    {
        //Out of bounds.
        if (index >= size_ || index < 0)
            throw_exception("invalid index called within remove().");

        //Remove value.
        for (int i = index; i < size_; i++)
            *(x_ + i) = *(x_ + (i + 1));

        //Resize.
        if (needs_resize(size_ - 1))
            resize(size_ - 1);

        size_--;

        return *this;
    }


    //Inserts a value on the end of the DynArr.
    DynArr<T>& push_back(const T data)
    {
        if (needs_resize(size_ + 1))
            resize(size_ + 1);

        *(x_ + size_) = data;

        size_++;

        return *this;
    }


    //Removes the value at the end of the DynArr.
    DynArr<T>& pop_back()
    {
        if (size_ == 0)
            throw_exception("cannot pop_back empty DynArr.");

        if (needs_resize(size_ - 1))
            resize(size_ - 1);

        size_--;

        return *this;
    }


    //Returns value at the back of the DynArr as a reference.
    T& back()
    {
        return *(x_ + (size_ - 1));
    }


    //Returns value at the back of the DynArr as a const.
    T back() const
    {
        return *(x_ + (size_ - 1));
    }


    //Resizes the DynArr to a given size.
    void resize(const unsigned int size)
    {
        T* x;

        //Allocate double space so you dont call resize() as much.
        capacity_ = size * 2;

        //If empty.
        if (capacity_ == 0)
            x = nullptr;
        else
        {
            //Allocate space.
            x = new T[capacity_];

            //Allocation failed.
            if (x == nullptr)
                throw_exception("memory allocation returns NULL.");

            //Copy values into new array.
            for (int i = 0; i < (size_ > size ? size : size_); i++)
                *(x + i) = *(x_ + i);
        }

        delete[] x_;
        x_ = x;
        
        return;
    }


    //Prints DynArr values, size, and capacity.
    inline void print() const
    {
        std::cout << *this << ", size:" << size_ <<
            ", capacity:" << capacity_ << '\n';
    
        return;
    }

};


//Prints out values of the DynArr.
template<typename T>
std::ostream& operator<<(std::ostream& out, const DynArr<T> a)
{
    out << '[';
    for (int i = 0; i < a.size(); i++)
    {
        out << a[i];
        if (i != a.size() - 1)
            out << ", ";
    }
    out << ']';
        
    return out;
}


//Takes an input integer to allocate space
//for that many values into the DynArr.
template<typename T>
std::istream& operator>>(std::istream& in, DynArr<T>& a)
{
    int total;

    std::cout << "Input amount of values: ";
    in >> total;

    if (total < 0)
        DynArr::throw_exception("Cannot allocate negative spaces.");

    if (a.needs_resize(total))
        a.resize(total);
    a.size_ = total;

    for (int i = 0; i < a.size(); i++)
        in >> a[i];
        
    return in;
}

#endif