#include <functional>
#include <algorithm>
#include <string>
#include <cstring>
#include <stdexcept>
#include <utility> // std::exchange
#include "PtrCStringVector.h"

#include <iostream>
using namespace std;

//* --------------------------------------------------------
//*                      CONSTRUCTOR                        
//* --------------------------------------------------------
PtrCStringVector::PtrCStringVector() : size_(0), capacity_(1), data_(new char *[1])
{
    data_[0] = nullptr;
}

PtrCStringVector::PtrCStringVector(const PtrCStringVector &srcPtrCStringVector)
{
    size_ = capacity_ = 0;
    copy(srcPtrCStringVector);
}

PtrCStringVector::~PtrCStringVector()
{
    for (size_t i = 0; i < size_; ++i)
    {
        delete[] data_[i];
    }
    delete[] data_;
}
//* --------------------------------------------------------
//*                       OPERATOR                          
//* --------------------------------------------------------
PtrCStringVector &PtrCStringVector::operator=(const PtrCStringVector &source)
{
    if (this == &source)
        return *this;

    copy(source);

    return *this;
}

PtrCStringVector &PtrCStringVector::operator=(PtrCStringVector &&source)
{

    if (this == &source)
        return *this;

    move(std::move(source));

    return *this;
}

PtrCStringVector PtrCStringVector::operator+(const PtrCStringVector &anotherVector) const
{
    PtrCStringVector *result = new PtrCStringVector();
    result->reserve(size_ + anotherVector.size_);
    result->size_ = size_ + anotherVector.size_;
    result->capacity_ = result->size_;

    for (size_t i = 0; i < size_; ++i)
    {
        result->data_[i] = new char[strlen(data_[i]) + 1];
        strcpy(result->data_[i], data_[i]);
    }
    for (size_t i = size_; i < result->size_; ++i)
    {
        result->data_[i] = new char[strlen(anotherVector.data_[i - size_]) + 1];
        strcpy(result->data_[i], anotherVector.data_[i - size_]);
    }

    return *result;
}

char *PtrCStringVector::operator[](size_t index)
{
    if (index >= size_)
    {
        throw out_of_range("Index out of range");
    }
    else
    {
        return data_[index];
    }
}
const char *PtrCStringVector::operator[](size_t index) const noexcept
{
    if (index >= size_)
    {
        return "";
    }
    else
    {
        return data_[index];
    }
}

PtrCStringVector PtrCStringVector::operator&(const PtrCStringVector &rhs) const
{
    PtrCStringVector *result = new PtrCStringVector;
    result->capacity_ = std::max(size_, rhs.size_);
    result->reserve(result->capacity_);
    result->size_ = result->capacity_;
    for (size_t i = 0; i < result->size_; i++)
    {
        size_t dlugosc = 1;

        if(i < size_)
            dlugosc += strlen(data_[i]);
        
        if(i < rhs.size_)
            dlugosc += strlen(rhs.data_[i]);

        result->data_[i] = new char[dlugosc];

        if(i < size_)
            strcpy(result->data_[i], data_[i]);
        if(i < rhs.size_)
            strcat(result->data_[i], rhs.data_[i]);
    }
    return *result;
}

//* --------------------------------------------------------
//*                        METHOD                           
//* --------------------------------------------------------
void PtrCStringVector::push_back(const char *text2Add)
{
    if ((capacity_ - size_) > 0)
    {
        data_[size_] = new char[strlen(text2Add) + 1];
        strcpy(data_[size_], text2Add);
        size_++;
    }
    else
    {

        reserve(capacity_ * 2);

        data_[size_] = new char[strlen(text2Add) + 1];
        strcpy(data_[size_], text2Add);
        size_++;
    }
}

void PtrCStringVector::free()
{
    for (size_t i = 0; i < size_; i++)
    {
        delete[] data_[i];
    }

    if (capacity_ > 0)
        delete[] data_;

    data_ = nullptr;
    size_ = capacity_ = 0;
}

void PtrCStringVector::copy(const PtrCStringVector &other)
{
    free();
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = new char *[capacity_];
    for (size_t i = 0; i < size_; i++)
    {
        data_[i] = new char[strlen(other.data_[i]) + 1];
        strcpy(data_[i], other.data_[i]);
    }
}
void PtrCStringVector::move(PtrCStringVector &&other)
{
    free();
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = other.data_;
    other.data_ = nullptr;
    other.capacity_ = other.size_ = 0;
}

void PtrCStringVector::reserve(size_t new_capacity)
{
    capacity_ = new_capacity;
    char **temp_array = new char *[capacity_];

    for (int i = 0; i < size_; i++)
    {
        temp_array[i] = data_[i];
    }

    delete[] data_;
    data_ = temp_array;
}
