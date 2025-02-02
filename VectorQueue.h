#ifndef VECTORQUEUE_H
#define VECTORQUEUE_H

#include <vector>
#include <stdexcept>
#include <iostream> // For debugging

template <typename T>
class VectorQueue {
private:
    std::vector<T> data;
    unsigned int head{0};

public:
    VectorQueue() = default;
    ~VectorQueue() = default;
    VectorQueue(const VectorQueue &other) = default;
    VectorQueue(VectorQueue &&other) noexcept = default;
    VectorQueue& operator=(const VectorQueue &other) = default;
    VectorQueue& operator=(VectorQueue &&other) noexcept = default;

    void enqueue(T value);
    T dequeue();
    T front() const;
    int size() const;
    bool isEmpty() const;
};

template<typename T>
void VectorQueue<T>::enqueue(T value)
{
    data.push_back(value);
}

template<typename T>
T VectorQueue<T>::dequeue()
{
    if (isEmpty())
        throw std::out_of_range("VectorQueue is empty");

    T value = data[head++];

    // Reset vector if all elements are dequeued
    if (head == data.size()) {
        data.clear();
        head = 0;
    }

    return value;
}

template<typename T>
T VectorQueue<T>::front() const
{
    if (isEmpty())
        throw std::out_of_range("VectorQueue is empty");

    return data[head];
}

template<typename T>
int VectorQueue<T>::size() const
{
    return head > data.size() ? 0 : data.size() - head;
}

template<typename T>
bool VectorQueue<T>::isEmpty() const
{
    return head >= data.size();
}

#endif // VECTORQUEUE_H