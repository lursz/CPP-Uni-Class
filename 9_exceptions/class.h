#ifndef CLASS_H
#define CLASS_H

#include <iostream>
#include <string>
#include <iomanip>
#include <complex>

//* ---------------------- Object --------------------------
class Object
{
public:
    virtual ~Object(){};

    virtual void print_value() = 0;
    virtual void multiply(int multiplier) = 0;
};

//* --------------------- IntObject ------------------------
class IntObject: public Object
{
private:
    int value;
    static int sum;
    static bool exists;

public:
    IntObject(const int &input);
    ~IntObject();
    void IntSum();
    static void print_sum();
    void print_value();
    void multiply(int multiplier);
};
//* ------------------- ComplexObject ----------------------
class ComplexObject: public Object
{
private:
    static bool exists;
    std::complex<int> value;
    static std::complex<int> sum;
public:
    ComplexObject(std::complex<int> &input);
    ~ComplexObject();
    void ComplexSum();
    static void print_sum();
    void print_value();
    void multiply(int multiplier);
};
//* ------------------- StringObject -----------------------
class StringObject: public Object
{
private:
    static bool exists;
    std::string text;
    static std::string sum;

public:
    StringObject(const std::string &input);
    ~StringObject();
    StringObject &operator+=(const StringObject &input);
    void StringSum();
    static void print_sum();
    void print_value();
    void multiply(int multiplier);
};
//* ------------------- DoubleObject -----------------------
class DoubleObject: public Object
{
private:
    double value;
    static double sum;
    static bool exists;

public:
    DoubleObject(const double &input);
    ~DoubleObject();
    void DoubleSum();
    static void print_sum();
    void print_value();
    void multiply(int multiplier);
};

#endif // CLASS_H