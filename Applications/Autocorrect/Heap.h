#ifndef HEAP_H
#define HEAP_H
#include <stdexcept>
#include <vector>

// Takes in a Compare struct, otherwise is defaulted as a max heap.
template <typename T, typename Compare = std::less<T>>
class Heap
{
public:
    Heap();
    void push(const T& data);
    const T& top() const;
    bool empty() const;
    int size() const;
    void pop();
private:
    int getRightChildIndex(const int& parentIndex) const;
    int getLeftChildIndex(const int& parentIndex) const;
    int getMaxChildIndex(const int& parentIndex) const;
    int getParentIndex(const int& childIndex) const;
    void reheapifyDown(const int& parentIndex);
    void reheapifyUp(const int& childIndex);
    std::vector<T> data;
    Compare compare;
};

#include "Heap.cpp"
#endif //HEAP_H