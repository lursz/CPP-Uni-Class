#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

#include "simpleString.h"

int SimpleString::instances_ = 0;

SimpleString::SimpleString() : size_(1), data_(new char[1]), capacity_(1)
{
    instances_++;

    data_[0] = 0;
}

SimpleString::SimpleString(const char *text)
{
    instances_++;
    int l = strlen(text) + 1; // we don't count 0 at the end
    data_ = new char[l];
    capacity_ = l;
    size_ = l;

    for (int i = 0; i < l; i++)
    {
        data_[i] = text[i];
    }
}
SimpleString::SimpleString(const SimpleString &text)
{
    instances_++;

    int l = text.size_;
    data_ = new char[l];
    capacity_ = l;
    size_ = l;

    for (int i = 0; i < l; i++)
    {
        data_[i] = text.data_[i];
    }
}
SimpleString::~SimpleString()
{
    instances_--;

    delete[] data_;
}
// ------------------------
int SimpleString::size() const
{
    return size_ - 1;
}
int SimpleString::capacity() const
{
    return capacity_ - 1;
}
const char *SimpleString::data() const
{
    return data_;
}
const char *SimpleString::c_str() const
{
    return data_;
}
int SimpleString::instances()
{
    return instances_;
}
// ------------------------

void SimpleString::assign(const char *new_text)
{
    int l = strlen(new_text) + 1;
    if (size_ < l)
    {
        delete[] data_;
        capacity_ = l;

        data_ = new char[l];
    }
    for (int i = 0; i < l; i++)
    {
        data_[i] = new_text[i];
    }

    size_ = l;
}
bool SimpleString::equal_to(SimpleString nowy, bool case_sensitive) const
{

    if (size_ == nowy.size_)
    {
        if (case_sensitive != true)
        {
            for (int i = 0; i < size_; i++)
            {
                if (toupper(data_[i]) != toupper(nowy.data_[i]))
                    return false;
            }
            return true;
        }
        for (int i = 0; i < size_; i++)
        {
            if (data_[i] != nowy.data_[i])
                return false;
        }
        return true;
    }
    return false;
}
void SimpleString::append(SimpleString value_to_add)
{
    int shared_l = size_ + value_to_add.size();
    char *temp_array = new char[shared_l];
    int i = 0;
    for (; i < size_ - 1; i++)
        temp_array[i] = this->data_[i];
    for (; i < shared_l; i++)
        temp_array[i] = value_to_add.data_[i - size_ + 1];
    delete[] data_;
    this->data_ = temp_array;
    capacity_ = shared_l;
    size_ = shared_l;
}
