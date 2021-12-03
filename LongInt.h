//Name: Grant Clark
//Date: November 29th, 2021
//File: LongInt.h

#ifndef LONG_INT_H
#define LONG_INT_H

#include <iostream>
#include <vector>
#include <climits> //for INT_MAX

class LongInt
{
public:
    LongInt();
    LongInt(const char[]);
    LongInt(const int);

    inline
    int size() const { return x_.size(); }

    //Operator[] returns the digit value at the i'th number
    //in the LongInt from left to right. So, if the LongInt
    //l is "12345", then l[1] = 2.
    inline
    int operator[](const int i) const { return x_[(x_.size() - 1) - i]; }

    //1 == positive, -1 == negative.
    inline
    int sign() const { return sign_; }
    inline
    int& sign() { return sign_; }

    const LongInt& operator=(const LongInt&);
    const LongInt& operator=(const char[]);
    const LongInt& operator=(const int);

    bool operator==(const LongInt&) const;
    bool operator!=(const LongInt&) const;
    bool operator> (const LongInt&) const;
    bool operator>=(const LongInt&) const;
    bool operator< (const LongInt&) const;
    bool operator<=(const LongInt&) const;

    LongInt & operator+=(const LongInt&);
    LongInt   operator+(const LongInt&) const;
    LongInt   operator+() const;
    LongInt   operator++(const int);
    LongInt & operator++();
                      
    LongInt & operator-=(const LongInt&);
    LongInt   operator-(const LongInt&) const;
    LongInt   operator-();
    LongInt   operator--(const int);
    LongInt & operator--();

    LongInt & operator*=(const LongInt&);
    LongInt   operator*(const LongInt&) const;

    LongInt & operator/=(const LongInt&);
    LongInt   operator/(const LongInt&) const;

    LongInt & operator%=(const LongInt&);
    LongInt   operator%(const LongInt&) const;

    //Absolute Value.
    LongInt abs() const;

    LongInt & multeq_tenpower(const int);
    LongInt & multeq_digit(const int);

    int int_val() const;

private:   
    std::vector<int> x_;
    int sign_;
};

bool operator==(const int, const LongInt&);
bool operator!=(const int, const LongInt&);
bool operator> (const int, const LongInt&);
bool operator>=(const int, const LongInt&);
bool operator< (const int, const LongInt&);
bool operator<=(const int, const LongInt&);

LongInt operator+(const int, const LongInt&);
LongInt operator-(const int, const LongInt&);
LongInt operator*(const int, const LongInt&);
LongInt operator/(const int, const LongInt&);

int & operator+=(int &, const LongInt&);
int & operator-=(int &, const LongInt&);
int & operator*=(int &, const LongInt&);
int & operator/=(int &, const LongInt&);
int & operator%=(int &, const LongInt&);

LongInt abs(const LongInt &);

std::ostream & operator<<(std::ostream&, const LongInt&);

class DivideByZeroError{};
class IntConversionOverflowError{};

#endif
