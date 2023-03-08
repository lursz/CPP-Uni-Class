#ifndef DOUBLE_STRING_H
#define DOUBLE_STRING_H

#include <iostream>
#include <string>
#include <iomanip>

class StringObject
{
private:
    std::string text;
    static bool exists;
    static std::string sum;

public:
    StringObject(const std::string &input);
    ~StringObject();
    StringObject &operator+=(const StringObject &input);
    void StringSum();
    static void print();
};

class DoubleObject
{
private:
    double value;
    static double sum;
    static bool exists;

public:
    DoubleObject(const double &input);
    ~DoubleObject();
    void DoubleSum();
    static void print();
};

#endif // DOUBLE_STRING_H