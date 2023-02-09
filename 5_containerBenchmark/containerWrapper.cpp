#include <iostream>
#include <algorithm> // std::sort, std::find, std::copy
#include <iterator>  // std::distance, std::advance, std::back_inserter
#include <limits>    // std::numeric_limits<size_t>::max()
#include <numeric>   // std::accumulate()

using namespace std;

#include "containerWrapper.h"

VectorWrapper::VectorWrapper(const value_type array[], int n)
{
    for (size_t i = 0; i < n; i++)
        impl_.push_back(array[i]);
}
VectorWrapper::~VectorWrapper() {}

// ------------------------

void VectorWrapper::push_back(const value_type &element)
{
    impl_.push_back(element);
}
void VectorWrapper::push_front(const value_type &element)
{
    impl_.insert(impl_.begin(), element);
}

void VectorWrapper::insert(const value_type &element, size_t position)
{
    impl_.insert(impl_.begin() + position, element);
}

size_t VectorWrapper::size() const
{
    return impl_.size();
}

VectorWrapper::value_type &VectorWrapper::at(size_t position)
{
    return impl_.at(position);
}

void VectorWrapper::sort()
{
    std::sort(impl_.begin(), impl_.end());
}

void VectorWrapper::erase(size_t position)
{
    impl_.erase(impl_.begin() + position);
}

/// @brief metoda mająca za zadanie zwrócenie sumy wszystkich elementów
VectorWrapper::value_type VectorWrapper::count() const
{
    value_type sum = 0;
    for (int i = 0; i < size(); i++)
        sum += impl_[i];
    return sum;
}

size_t VectorWrapper::find(const value_type &needle) const
{
    auto it = std::find(impl_.begin(), impl_.end(), needle);

    if (it == impl_.end())
        return std::numeric_limits<size_t>::max();
    return it - impl_.begin();
}

VectorWrapper::value_type VectorWrapper::pop_front()
{
    value_type first_element = impl_[0];

    impl_.erase(impl_.begin());

    return first_element;
}

IContainerWrapper::~IContainerWrapper() = default;
