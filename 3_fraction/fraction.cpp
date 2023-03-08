#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

#include "fraction.h"

#if IMPLEMENTED_classFractionExists
/*
#ifndef _MSC_FULL_VER // if not Visual Studio Compiler
#warning "Klasa jest do zaimplementowania. Instrukcja w pliku naglowkowym"
#else
#pragma message("Klasa jest do zaimplementowania. Instrukcja w pliku naglowkowym")
#endif
*/

int Fraction::removedFractions_ = 0;
const int Fraction::invalidDenominatorValue = 0;

// KONSTRUKTORY
Fraction::Fraction(int licznik, int mianownik, std::string nazwa_otrzymana):numerator(licznik), denominator(mianownik),fractionName(nazwa_otrzymana)
{

}
/*Fraction::Fraction():numerator(0), denominator(1), fractionName("kompilator_inaczej_dawal_blad")
{}*/
Fraction::~Fraction()
{
    removedFractions_++;
}

// GET I SET
int Fraction::getNumerator() const
{
    return numerator;
}
void Fraction::setNumerator(int temp_numerator)
{
    numerator = temp_numerator;
}
int Fraction::getDenominator() const
{
    return denominator;
}
void Fraction::setDenominator(int temp_denominator)
{
    denominator = temp_denominator;
}

// INNE METODY
int Fraction::removedFractions()
{
    return removedFractions_;
}
std::string Fraction::getFractionName() const
{
    return fractionName;
}

void Fraction::save(std::ostream &os) const
{
    os << numerator << '/' << denominator;
}
void Fraction::load(std::istream &is)
{
    std::string dane_in;

    is >> dane_in;

    numerator = denominator = 0;

    int i = 0;
    for (; dane_in[i] != '/'; i++)
        numerator = numerator * 10 + static_cast<int>(dane_in[i] - '0');

    i++;
    for (; dane_in[i]; i++)
        denominator = denominator * 10 + static_cast<int>(dane_in[i] - '0');
}
int Fraction::getInvalidDenominatorValue()
{
    return invalidDenominatorValue;
}

int Fraction::getDefaultDenominatorValue()
{
    return defaultDenominatorValue;
}

#endif // IMPLEMENTED_classFractionExists