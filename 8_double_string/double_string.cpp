#include "double_string.h"

std::string StringObject::sum = "";
bool StringObject::exists = false;


double DoubleObject::sum = 0;
bool DoubleObject::exists = false;

//*StringObject
StringObject::StringObject(const std::string &input) : text(input)
{
    exists = true;
    StringSum();
}
StringObject::~StringObject()
{
}
StringObject &StringObject::operator+=(const StringObject &input)
{
    text += input.text;
    return *this;
}
void StringObject::StringSum()
{
    sum += this->text;
}
void StringObject::print()
{
    if (exists)
        std::cout << "StringObject(\"" << sum << "\")" << std::endl;
}

//* DoubleObject

DoubleObject::DoubleObject(const double &input) : value(input)
    {
        DoubleSum();
        exists = true;
    }
    DoubleObject::~DoubleObject()
    {
    }

    void DoubleObject::DoubleSum() 
    {
        sum += this -> value;
    }
    void DoubleObject::print()
    {
        if(exists)
            std::cout << "DoubleObject(" << sum << ")" << std::endl;
    }