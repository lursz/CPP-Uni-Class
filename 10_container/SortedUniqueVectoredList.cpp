#include <string>
#include <array>
#include <stdexcept> // std::out_of_range
#include "SortedUniqueVectoredList.h"

#include <iostream>

using namespace std;

/** class SortedUniqueVectoredList::Bucket
 * @param size ilosc elementow w kubelku, tworzac pusty ma byc 0
 * @param values elementy kubelka, jako tablica statyczna
 * @param BUCKET_SIZE ilosc elementow w statycznej tablicy
 * @param bucketCount_ ilosc kubelkow
 * @param next wskaznik na nastepny @ref Bucket, a jesli takiego nie ma na nullptr
 * @param previous wskaznik na poprzedni @ref Bucket, a jesli takiego nie ma na nullptr
 * @note jest to klasa zrobiona przy pomocy [idiomu PIMPL](https://en.cppreference.com/w/cpp/language/pimpl),
 *       ktory polega na tym, ze w klasie zewnetrznej jest jedynie deklaracja klasy wewnetrznej, ktora jest zaimplementowana w pliku zrodlowym **/
// ------------------------
struct SortedUniqueVectoredList::Bucket
{
    constexpr static size_t BUCKET_SIZE = 10;

    std::array<std::string, BUCKET_SIZE> values;
    size_t size = 0;

    Bucket *next = nullptr;
    Bucket *previous = nullptr;
};

// ------------------------
SortedUniqueVectoredList::SortedUniqueVectoredList(const SortedUniqueVectoredList &source)
{
    copy(source);
}

SortedUniqueVectoredList::SortedUniqueVectoredList(SortedUniqueVectoredList &&another)
{
    this->move(std::move(another));
}

SortedUniqueVectoredList::~SortedUniqueVectoredList()
{
    free();
}

// ------------------------
void SortedUniqueVectoredList::insert(const string &value)
{
    // ZAWIERA
    if (contains(value))
        return;
    // PUSTY
    if (head == nullptr)
    {
        allocate_new_bucket();
        head->values[0] = value;
        head->size = 1;
        size_++;

        return;
    }

    if (size_ + 1 > capacity_)
        allocate_new_bucket();

    // NORMALNY

    bool found = false;
    int ile_przeszedlem = 0;
    std::string string_cache = "";
    Bucket *bucket_entity = head;

    while (!found)
    {
        // index docelowy
        int i = 0;
        while (i < bucket_entity->size && i < Bucket::BUCKET_SIZE)
        {
            if (bucket_entity->values[i] > value)
            {
                found = true;
                break;
            }
            i++;
            ile_przeszedlem++;
        }

        if (!found && ile_przeszedlem < size_)
        {
            bucket_entity = bucket_entity->next;
        }
        else
        {
            Bucket *current_bucket = tail;
            for (int j = size_; j > ile_przeszedlem; j--)
            {
                if (j % Bucket::BUCKET_SIZE == 0)
                {
                    current_bucket->values[0] = current_bucket->previous->values[Bucket::BUCKET_SIZE - 1];
                    current_bucket = current_bucket->previous;
                }
                else
                    current_bucket->values[j % Bucket::BUCKET_SIZE] = current_bucket->values[(j - 1) % Bucket::BUCKET_SIZE];
            }

            if (i < 10)
            {
                bucket_entity->values[i] = value;
            }
            else
            {
                bucket_entity->next->values[0] = value;
            }
            tail->size++;
            size_++;

            return;
        }
    }
}

SortedUniqueVectoredList::operator std::string() const
{
    std::string result = "";
    Bucket *bucket_entity = head;

    int ile = 0;
    while (bucket_entity != nullptr)
    {
        for (int i = 0; i < bucket_entity->size; i++)
        {
            result += bucket_entity->values[i];
        }

        bucket_entity = bucket_entity->next;
        ile++;
    }
    return result;
}

void SortedUniqueVectoredList::allocate_new_bucket()
{

    capacity_ += Bucket::BUCKET_SIZE;
    bucketCount_++;

    if (bucketCount_ == 1)
    {
        head = new Bucket;
        tail = head;
        head->size = 0;
    }
    else
    {
        tail->next = new Bucket;
        tail->next->previous = tail;
        tail = tail->next;
        tail->size = 0;
    }
}

void SortedUniqueVectoredList::free()
{
    if (capacity_ == 0)
        return;

    size_ = 0;
    bucketCount_ = 0;
    capacity_ = 0;

    while (head != nullptr)
    {
        Bucket *temp_pointer = head;
        head = head->next;
        delete temp_pointer;
    }

    tail = nullptr;
    head = nullptr;
}

void SortedUniqueVectoredList::move(SortedUniqueVectoredList &&another)
{
    copy(another);
    another.free();
}

void SortedUniqueVectoredList::copy(const SortedUniqueVectoredList &other)
{
    free();
    size_ = other.size_;
    bucketCount_ = other.bucketCount_;
    capacity_ = other.capacity_;

    head = new Bucket;
    tail = head;

    Bucket *bucket_entity = other.head;

    while (bucket_entity != nullptr)
    {
        for (int i = 0; i < bucket_entity->size; i++)
            tail->values[i] = bucket_entity->values[i];

        tail->size = bucket_entity->size;

        if (bucket_entity->next != nullptr)
        {
            tail->next = new Bucket;
            tail->next->previous = tail;
            tail = tail->next;
        }

        bucket_entity = bucket_entity->next;
    }
}

bool SortedUniqueVectoredList::contains(const string &value) const
{
    Bucket *bucket_iterator = head;
    while (bucket_iterator != nullptr)
    {
        for (int i = 0; i < bucket_iterator->size; i++)
        {

            if (bucket_iterator->values[i] == value)
            {
                return true;
            }
        }

        bucket_iterator = bucket_iterator->next;
    }

    return false;
}
// ------------------------
SortedUniqueVectoredList &SortedUniqueVectoredList::operator=(SortedUniqueVectoredList &&another)
{
    if (this != &another)
    {
        this->move(std::move(another));
    }
    return *this;
}

SortedUniqueVectoredList SortedUniqueVectoredList::operator-(const SortedUniqueVectoredList &another) const
{
    SortedUniqueVectoredList result;

    Bucket *temp_bucket = head;
    while (temp_bucket != nullptr)
    {
        for (int i = 0; i < temp_bucket->size; i++)
        {
            if (another.contains(temp_bucket->values[i]))
                continue;

            result.insert(temp_bucket->values[i]);
        }
        temp_bucket = temp_bucket->next;
    }
    return result;
}

SortedUniqueVectoredList &SortedUniqueVectoredList::operator*=(const size_t howManyTimesMultiply)
{
    Bucket *bucket_entity = head;

    while (bucket_entity != nullptr)
    {
        for (int i = 0; i < bucket_entity->size; i++)
        {
            std::string temp = bucket_entity->values[i];
            bucket_entity->values[i] = "";

            for (int j = 0; j < howManyTimesMultiply; j++)
                bucket_entity->values[i] += temp;
        }
        bucket_entity = bucket_entity->next;
    }

    return *this;
}

string &SortedUniqueVectoredList::operator[](size_t index)
{
    int bucket_index = index % Bucket::BUCKET_SIZE;
    int bucket_number = index / Bucket::BUCKET_SIZE;

    if (bucket_number >= bucketCount_)
        throw std::out_of_range("Index out of range");

    Bucket *bucket_entity = head;
    for (int i = 0; i < bucket_number; i++)
        bucket_entity = bucket_entity->next;

    if (bucket_index >= bucket_entity->size)
        throw std::out_of_range("Index out of range");

    return bucket_entity->values[bucket_index];
}

const string &SortedUniqueVectoredList::operator[](size_t index) const
{
    int bucket_index = index % Bucket::BUCKET_SIZE;
    int bucket_number = index / Bucket::BUCKET_SIZE;

    if (bucket_number >= bucketCount_)
        throw std::out_of_range("Index out of range");

    Bucket *bucket_entity = head;
    for (int i = 0; i < bucket_number; i++)
        bucket_entity = bucket_entity->next;

    return bucket_entity->values[bucket_index];
}

SortedUniqueVectoredList &SortedUniqueVectoredList::operator=(const SortedUniqueVectoredList &another)
{
    copy(another);

    return *this;
}

//// OPCJONALNE
void SortedUniqueVectoredList::erase(const string &value)
{
    /// @todo zaimplementuj, szczegoly w pliku naglowkowym (opcjonalne zadanie)
}