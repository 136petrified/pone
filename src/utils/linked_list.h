/*   Created:  10-06-2025
 *   Modified: 10-19-2025
 */

#pragma once

#include <cstdio>
#include <stdexcept>

namespace pone {

template <typename T>
class Node {
    T m_data;
    Node *m_next;

   public:
    Node(const T &data, Node *next) : m_data{data}, m_next{next} {}
};

template <typename T>
class LinkedList {
   public:
    LinkedList();
    ~LinkedList();
};

template <typename T>
class UnsortedLinkedList : public LinkedList<T> {
    Node<T> *m_head, m_tail;
    std::size_t m_size;

    UnsortedLinkedList();

    bool empty() const;
    void insert(const T &data);
    Node<T> *find(const T &data) const;
    void remove(const T &data);
    std::size_t size() const;

    T &operator[](std::size_t idx);
    const T &operator[](std::size_t idx) const;

    ~UnsortedLinkedList();
};

// TODO: SortedLinkedList

template <typename T>
UnsortedLinkedList<T>::UnsortedLinkedList()
    : m_head{nullptr}, m_tail{nullptr}, m_size{0} {}

template <typename T>
bool UnsortedLinkedList<T>::empty() const {
    return m_size <= 0;
}

template <typename T>
void UnsortedLinkedList<T>::insert(const T &data) {
    if (empty()) {
        m_head = m_tail = new Node<T>{data, m_tail};
    } else {
        m_tail->next = new Node<T>{data, nullptr};
    }

    ++m_size;
}

template <typename T>
Node<T> *UnsortedLinkedList<T>::find(const T &data) const {
    for (Node<T> *curr = m_head; curr != nullptr; curr = curr->next) {
        if (curr->data == data) {
            return curr;
        }
    }

    return nullptr;
}

template <typename T>
void UnsortedLinkedList<T>::remove(const T &data) {
    Node<T> *tmp, *curr, *prev;

    if (m_head == nullptr) {
        return;
    } else if (m_head->data == data) {
        tmp = m_head->next;
        delete m_head;
        m_head = tmp;
        --m_size;
        return;
    }

    for (curr = m_head->next, prev = m_head; curr != nullptr;
         curr = curr->next) {
        if (curr->data == data) {
            tmp        = curr;
            prev->next = curr->next;
            delete tmp;
            --m_size;
            return;
        }
    }
}

template <typename T>
std::size_t UnsortedLinkedList<T>::size() const {
    return m_size;
}

template <typename T>
T &UnsortedLinkedList<T>::operator[](std::size_t idx) {
    Node<T> *curr;
    std::size_t i;

    for (curr = m_head, i = 0; curr != nullptr; curr = curr->next, ++i) {
        if (i == idx) {
            return curr->data;
        }
    }

    throw std::runtime_error("");  // TODO: Replace with OutOfBoundsException
}

template <typename T>
const T &UnsortedLinkedList<T>::operator[](std::size_t idx) const {
    Node<T> *curr;
    std::size_t i;

    for (curr = m_head, i = 0; curr != nullptr; curr = curr->next, ++i) {
        if (i == idx) {
            return curr->data;
        }
    }

    throw std::runtime_error("");  // TODO: Replace with OutOfBoundsException
}

}  // namespace pone
