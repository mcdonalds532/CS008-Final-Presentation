#ifndef HEAP_CPP
#define HEAP_CPP
#include "Heap.h"

template <typename T, typename Compare>
Heap<T, Compare>::Heap() {}

template <typename T, typename Compare>
const T& Heap<T, Compare>::top() const
{
    if(empty())
        throw std::out_of_range("Empty Heap");
    return data[0];
}

template <typename T, typename Compare>
void Heap<T, Compare>::push(const T& data)
{
    this->data.push_back(data);
    reheapifyUp(size() - 1);
}

template <typename T, typename Compare>
void Heap<T, Compare>::pop()
{
    if(empty())
        return;
    std::swap(data[0], data[size() - 1]);
    data.pop_back();
    if(!empty())
        reheapifyDown(0);
}

template <typename T, typename Compare>
int Heap<T, Compare>::size() const
{
    return data.size();
}

template <typename T, typename Compare>
bool Heap<T, Compare>::empty() const
{
    return data.empty();
}

template <typename T, typename Compare>
int Heap<T, Compare>::getParentIndex(const int& childIndex) const
{
    return (childIndex - 1) / 2;
}

template <typename T, typename Compare>
int Heap<T, Compare>::getLeftChildIndex(const int& parentIndex) const
{
    return parentIndex * 2 + 1;
}

template <typename T, typename Compare>
int Heap<T, Compare>::getRightChildIndex(const int& parentIndex) const
{
    return parentIndex * 2 + 2;
}

template <typename T, typename Compare>
int Heap<T, Compare>::getMaxChildIndex(const int& parentIndex) const
{
    const int leftChildIndex = getLeftChildIndex(parentIndex);
    const int rightChildIndex = getRightChildIndex(parentIndex);
    const int size = this->size();
    if(leftChildIndex >= size && rightChildIndex >= size)
        return parentIndex;
    else if(leftChildIndex >= size)
        return rightChildIndex;
    else if(rightChildIndex >= size)
        return leftChildIndex;
    return compare(data[leftChildIndex], data[rightChildIndex]) ? rightChildIndex : leftChildIndex;
}

template <typename T, typename Compare>
void Heap<T, Compare>::reheapifyUp(const int& childIndex)
{
    const int parentIndex = getParentIndex(childIndex);
    if(!childIndex)
        return;
    if(compare(data[parentIndex], data[childIndex]))
    {
        std::swap(data[parentIndex], data[childIndex]);
        reheapifyUp(parentIndex);
    }
}

template <typename T, typename Compare>
void Heap<T, Compare>::reheapifyDown(const int& parentIndex)
{
    const int maxChildIndex = getMaxChildIndex(parentIndex);
    if(maxChildIndex == parentIndex || compare(data[maxChildIndex], data[parentIndex]))
        return;
    std::swap(data[maxChildIndex], data[parentIndex]);
    reheapifyDown(maxChildIndex);
}

#endif //HEAP_CPP