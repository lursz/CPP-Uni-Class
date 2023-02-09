#include "class.h"

std::string StringObject::sum = "";
bool StringObject::exists = false;

double DoubleObject::sum = 0;
bool DoubleObject::exists = false;

std::complex<int> ComplexObject::sum = 0;
bool ComplexObject::exists = false;

int IntObject::sum = 0;
bool IntObject::exists = false;

//* --------------------------------------------------------
//*                       IntObject
//* --------------------------------------------------------
IntObject::IntObject(const int &input) : value(input)
{
    exists = true;
    IntSum();
}
IntObject::~IntObject() {}
void IntObject::IntSum()
{
    sum += this->value;
}
void IntObject::print_sum()
{
    if (exists)
        std::cout << "IntObject(" << sum << ")" << std::endl;
}
void IntObject::print_value()
{
    if (exists)
        std::cout << "IntObject(" << value << ")" << std::endl;
}
void IntObject::multiply(int multiplier)
{
    sum *= multiplier;
}

//* --------------------------------------------------------
//*                     ComplexObject
//* --------------------------------------------------------
ComplexObject::ComplexObject(std::complex<int> &input) : value(input)
{
    exists = true;
    ComplexSum();
}

ComplexObject::~ComplexObject()
{
}
void ComplexObject::ComplexSum()
{
    sum += this->value;
}
void ComplexObject::print_sum()
{
    if (exists)
    {
        if (imag(sum) == 0)
            std::cout << "ComplexObject(" << real(sum) << ")" << std::endl;
        else if (imag(sum) > 0)
            std::cout << "ComplexObject(" << real(sum) << "+" << imag(sum) << 'i' << ")" << std::endl;
        else
            std::cout << "ComplexObject(" << real(sum) << "-" << imag(sum) << 'i' << ")" << std::endl;
    }
}
void ComplexObject::print_value()
{
    if (exists)
    {
        if (imag(value) == 0)
            std::cout << "ComplexObject(" << real(value) << ")" << std::endl;
        else if (imag(value) > 0)
            std::cout << "ComplexObject(" << real(value) << "+" << imag(value) << 'i' << ")" << std::endl;
        else
            std::cout << "ComplexObject(" << real(value) << imag(value) << 'i' << ")" << std::endl;
    }
}
void ComplexObject::multiply(int multiplier)
{
    sum *= multiplier;
}

//* --------------------------------------------------------
//*                     StringObject
//* --------------------------------------------------------
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
void StringObject::print_sum()
{
    if (exists)
        std::cout << "StringObject(\"" << sum << "\")" << std::endl;
}
void StringObject::print_value()
{
    if (exists)
        std::cout << "StringObject(\"" << text << "\")" << std::endl;
}
void StringObject::multiply(int multiplier)
{
    std::string string_copy = sum;
    sum = "";
    for (int i = 0; i < multiplier; i++)
    {
        sum += string_copy;
    }
}

//* --------------------------------------------------------
//*                     DoubleObject
//* --------------------------------------------------------
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
    sum += this->value;
}
void DoubleObject::print_sum()
{
    if (exists)
        std::cout << "DoubleObject(" << sum << ")" << std::endl;
}
void DoubleObject::print_value()
{
    if (exists)
        std::cout << "DoubleObject(" << value << ")" << std::endl;
}
void DoubleObject::multiply(int multiplier)
{
    sum *= multiplier;
}