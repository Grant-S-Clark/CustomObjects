//Name: Grant Clark
//Date: November ??, 2021
//File: LongInt.cpp

#include "LongInt.h"

LongInt::LongInt() : sign_(1)
{
    x_.resize(1);
    x_[0] = 0;
    
    return;
}


LongInt::LongInt(const char s[])
{
    //start_zeros records the number of zeros at the beginning of
    //the string before another number. num_start determines when
    //the number has started so we can start recording zeros.
    //This means that "00000000" still becomes just 0.
    //Thhis also means that "000024" becomes 24.
    int i = 0, start_zeros = 0;
    bool num_start = false;
    
    //Positive / zero
    if (s[0] != '-')
    {
        //Set sign
        sign_ = 1;

        //Set size.
        while (s[i] != '\0')
        {
            if (!num_start && s[i] == '0')
                start_zeros++;
            else if (!num_start)
                num_start = true;

            i++;
        }
        
        x_.resize(i - start_zeros);
        
        if (x_.size() == 0 && s[i - 1] == '0')
        {
            x_.resize(1);
            start_zeros--;
        }
        
        //Set digits.
        for (i = 0; i < x_.size(); i++)
        {
            //Set digit using ascii character of
            //the digit in the string.
            x_[(x_.size() - 1) - i] =
                static_cast<int>(s[i + start_zeros]) - 48;
        }
    }

    //Negative
    else
    {
        //Set sign
        sign_ = -1;

        //Set Size
        while (s[i] != '\0')
        {
            if (!num_start && s[i] == '0')
                start_zeros++;
            else if (!num_start)
                num_start = true;

            i++;
        }
        
        x_.resize(i - start_zeros - 1);
        
        if (x_.size() == 0 && s[i - 1] == '0')
        {
            x_.resize(1);
            start_zeros--;
        }
        
        //Set digits
        for (i = 0; i < x_.size(); i++)
        {
            //Set digit using ascii character of
            //the digit in the string.
            x_[(x_.size() - 1) - i] =
                static_cast<int>(s[i + start_zeros + 1]) - 48;
        }

        //If someone entered "-0", this makes sign positive.
        if (x_.size() == 1 && x_[0] == 0)
        {
            sign_ = 1;
        }
    }

    return;
}


LongInt::LongInt(const int num)
{
    if (num == 0)
    {
        sign_ = 1;
        x_.resize(1);
        x_[0] = 0;
    }

    else
    {
        //Set sign.
        if (num < 0)
            sign_ = -1;
        else
            sign_ = 1;

        //Set size.
        int i = 0, t = num;
        while (t != 0)
        {
            t /= 10;
            i++;
        }
        
        x_.resize(i);
        //Set digits
        for (i = 0; i < x_.size(); i++)
        {
            t = num;
            for (int j = 0; j < (x_.size() - 1) - i; j++)
                t /= 10;
            if (sign_ == -1)
                x_[(x_.size() - 1) - i] = (t % 10) * -1;
            else
                x_[(x_.size() - 1) - i] = t % 10;
        }
    }
    
    return;
}


const LongInt & LongInt::operator=(const LongInt & l)
{
    sign_ = l.sign();
    x_.resize(l.size());
    for (int i = 0; i < x_.size(); i++)
        x_[i] = l[(l.size() - 1) - i];

    return *this;
}


const LongInt & LongInt::operator=(const char x[])
{
    return *this = LongInt(x);
}


const LongInt & LongInt::operator=(const int i)
{
    return *this = LongInt(i);
}


bool LongInt::operator==(const LongInt & l) const
{
    if (this == &l)
        return true;
    
    if (sign_ != l.sign() ||
        x_.size() != l.size())
    {
        return false;
    }

    for (int i = 0; i < x_.size(); i++)
        if (x_[i] != l[(l.size() - 1) - i])
            return false;
    
    return true;
}


bool LongInt::operator!=(const LongInt & l) const
{
    return !(*this == l);
}


bool LongInt::operator>(const LongInt & l) const
{
    if (this == &l)
        return false;

    if (sign_ != l.sign())
        return (sign_ > l.sign() ? true : false);

    if (x_.size() != l.size())
        return (x_.size() > l.size() ? true : false);

    for (int i = x_.size() - 1; i >= 0; i--)
        if (x_[i] != l[(l.size() - 1) - i])
            return (x_[i] > l[(l.size() - 1) - i] ? true : false);

    //If equal.
    return false;
}


bool LongInt::operator>=(const LongInt & l) const
{
    return !(*this < l);
}


bool LongInt::operator<(const LongInt & l) const
{
    return l > *this;
}


bool LongInt::operator<=(const LongInt & l) const
{
    return !(*this > l);
}


LongInt& LongInt::operator+=(const LongInt & l)
{
    if (sign_ != l.sign())
    {
        LongInt t = l;
        t.sign() *= -1;
        
        return *this -= t;
    }

    //Add zeros in unfilled spaces, if any.
    if (l.size() > x_.size())
    {
        int og_size = x_.size();
        for (int i = 0; i < l.size() - og_size; i++)
            x_.push_back(0);
    }

    //Add values.
    for (int i = 0; i < l.size(); i++)
        x_[i] += l[(l.size() - 1) - i];

    //Adjust values for overflow
    for (int i = 0; i < x_.size(); i++)
    {
        if (x_[i] > 9)
        {
            if (i + 1 >= x_.size())
            {
                x_.push_back(0);
            }
            
            x_[i + 1] += x_[i] / 10;
            x_[i] %= 10;
        }
    }

    //Remove redundant zeros.
    for (int i = x_.size() - 1; i > 0; i--)
    {
        if (x_[i] == 0)
            x_.pop_back();
        else
            break;
    }

    return *this;
}


LongInt LongInt::operator+(const LongInt & l) const
{
    return LongInt(*this) += l;
}


LongInt LongInt::operator+() const
{
    return *this;
}


LongInt LongInt::operator++(const int i)
{
    LongInt ret = *this;

    *this += 1;
    
    return ret;
}


LongInt & LongInt::operator++()
{
    return *this += 1;
}


LongInt& LongInt::operator-=(const LongInt & l)
{
    if (sign_ != l.sign())
    {
        LongInt t = l;
        t.sign() *= -1;
        
        return *this += t;
    }

    //Add zeros in unfilled spaces, if any.
    if (l.size() > x_.size())
    {
        int og_size = x_.size();
        for (int i = 0; i < l.size() - og_size; i++)
            x_.push_back(0);
    }

    //Subtract values.
    for (int i = 0; i < l.size(); i++)
        x_[i] -= l[(l.size() - 1) - i];

    //Adjust values for underflow
    for (int i = 0, t; i < x_.size(); i++)
    {
        if (x_[i] < 0)
        {
            //Attempt to find next number.
            for (t = i + 1; t < x_.size(); t++)
            {
                if (x_[t] > 0)
                    break;
            }

            //If found.
            if (t != x_.size() && x_[t] > 0)
            {
                for (int j = t; j >= 0; j--)
                {
                    if (j == t)
                    {
                        x_[j] -= 1;
                        if (x_[j] == 0 && j == x_.size() - 1)
                            x_.pop_back();
                    }

                    else if (j == 0)
                        x_[j] += 10;
                    else
                        x_[j] += 9;
                }

                //Reset i.
                i = -1;
            }

            //If not found.
            else
            {
                //swap sign.
                sign_ *= -1;
                //Swap signs of all numbers.
                for (int j = 0; j < x_.size(); j++)
                    x_[j] *= -1;

                //Reset i.
                i = -1;
            }
        }
    }
    
    //This loop will correct overflow.
    for (int i = 0; i < x_.size(); i++)
    {
        if (x_[i] > 9)
        {
            if (i + 1 >= x_.size())
            {
                x_.push_back(0);
            }
            
            x_[i + 1] += x_[i] / 10;
            x_[i] %= 10;
        }
    }
    
    //Remove redundant zeros.
    for (int i = x_.size() - 1; i >= 0; i--)
    {
        if (x_[i] == 0)
            x_.pop_back();
        else
            break;
    }

    //If it is all just zeros in a row.
    if (x_.empty())
    {
        x_.push_back(0);
        if (sign_ == -1)
            sign_ = 1;
    }

    return *this;
}


LongInt LongInt::operator-(const LongInt & l) const
{
    return LongInt(*this) -= l;
}


LongInt LongInt::operator-()
{
    //Do not make a negative zero.
    if (*this != 0)
        sign_ *= -1;
    
    return *this;
}


LongInt LongInt::operator--(const int i)
{
    LongInt ret = *this;

    *this -= 1;
    
    return ret;
}


LongInt & LongInt::operator--()
{
    return *this -= 1;
}


LongInt & LongInt::operator*=(const LongInt & l)
{
    if (l == 0)
        *this = 0;

    else if (*this != 0)
    {
        LongInt sum = 0, term;

        for (int i = 0; i < l.size(); i++)
        {
            term = this->abs();
            term.multeq_digit(l[i]);
            term.multeq_tenpower((l.size() - 1) - i);
            sum += term;
        }

        if (sign_ != l.sign())
            sum.sign() = -1;
    
        *this = sum;
    }
    
    return *this;
}


LongInt LongInt::operator*(const LongInt & l) const
{
    return LongInt(*this) *= l;
}


LongInt & LongInt::operator/=(const LongInt & l)
{
    if (l == 0)
        throw DivideByZeroError();

    else if (abs() < l.abs())
        *this = 0;

    else
    {
        LongInt quotient = 0,
            this_abs = abs(),
            sub = l.abs(),
            temp = 0;

        for (int i = 0; i < x_.size(); i++)
        {
            temp += this_abs[i];
            
            while (temp - sub >= 0)
            {
                temp -= sub;
                quotient++;
            }
            
            if (i != x_.size() - 1)
            {
                quotient.multeq_tenpower(1);
                temp.multeq_tenpower(1);
            }
        }    

        if (sign_ != l.sign())
        {
            *this = quotient;
            sign_ = -1;
        }

        else
            *this = quotient;
    }

    return *this;
}


LongInt LongInt::operator/(const LongInt & l) const
{
    return LongInt(*this) /= l;
}


LongInt & LongInt::operator%=(const LongInt & l)
{
    return *this -= (l * (*this / l));
}


LongInt LongInt::operator%(const LongInt & l) const
{
    return LongInt(*this) %= l;
}


LongInt LongInt::abs() const
{
    LongInt ret = *this;
    
    if (ret.sign() == -1)
        ret.sign() *= -1;

    return ret;
}


LongInt & LongInt::multeq_tenpower(const int pow)
{
    if (pow > 0 && *this != 0)
        for (int i = 0; i < pow; i++)
            x_.insert(x_.begin(), 0);

    else
    {
        for (int i = 0; i > pow; i--)
        {
            if (x_.size() == 1)
            {
                *this = 0;
                break;
            }

            x_.erase(x_.begin());
        }
    }
    
    return *this;
}


LongInt & LongInt::multeq_digit(const int mult)
{
    if (mult == 0)
    {
        *this = LongInt(0);
        return *this;
    }
    
    for (int i = 0; i < x_.size(); i++)
        x_[i] *= mult;

    //-= 0 will correct overflow and negatives, if any.
    return *this -= 0;
}


int LongInt::int_val() const
{
    if (*this > INT_MAX || *this < INT_MIN)
    {
        throw IntConversionOverflowError();
    }
    
    int ret = 0;
    for (int i = 0, j; i < x_.size(); i++)
    {
        if (x_[i] != 0)
        {
            j = 1;
            for(int k = 0; k < i; k++)
                j *= 10;
            ret += (x_[i]) * j;
        }
    }

    if (sign_ == -1)
        ret *= -1;

    return ret;
}


LongInt::operator int() const
{
    return int_val();
}


/////////////////
///NON-MEMBERS///
/////////////////


bool operator==(const int i, const LongInt & l)
{
    return l == i;
}


bool operator!=(const int i, const LongInt & l)
{
    return l != i;
}


bool operator>(const int i, const LongInt & l)
{
    return !(l <= i);
}


bool operator>=(const int i, const LongInt & l)
{
    return !(l < i);
}


bool operator<(const int i, const LongInt & l)
{
    return !(l >= i);
}


bool operator<=(const int i, const LongInt & l)
{
    return !(l > i);
}


LongInt operator+(const int i, const LongInt & l)
{
    return l + i;
}


LongInt operator-(const int i, const LongInt & l)
{
    return LongInt(i) - l;
}


LongInt operator*(const int i, const LongInt & l)
{
    return l * i;
}


LongInt operator/(const int i, const LongInt & l)
{
    return l / i;
}


int & operator+=(int & i, const LongInt & l)
{
    return i += l.int_val();
}


int & operator-=(int & i, const LongInt & l)
{
    return i -= l.int_val();
}


int & operator*=(int & i, const LongInt & l)
{
    return i *= l.int_val();
}


int & operator/=(int & i, const LongInt & l)
{
    return i /= l.int_val();
}


int & operator%=(int & i, const LongInt & l)
{
    return i %= l.int_val();
}


LongInt abs(LongInt & l)
{
    return l.abs();
}


std::ostream & operator<<(std::ostream & cout, const LongInt & l)
{
    if (l.sign() == -1)
        cout << '-';
    for (int i = 0; i < l.size(); i++)
        cout << l[i];

    return cout;
}
