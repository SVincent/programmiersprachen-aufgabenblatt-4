#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP
#include <cstddef>

using namespace std;
// List.hpp

//Why does template class List appear twice?
template <typename T>
class List;

template <typename T>
struct ListNode {
    ListNode():
        value(),
        prev(nullptr),
        next(nullptr)
        {}

    ListNode(T const& v, ListNode* prev, ListNode* next):
        value(v),
        prev(prev),
        next(next)
        {}
        
    T value = T();
    ListNode* prev = nullptr;
    ListNode* next = nullptr;
};

template <typename T>
class ListIterator {
public:

private:
    ListNode <T >* node ;
};

template <typename T>
class ListConstIterator {
public:
// not implemented yet
// do not forget about the initialiser lists !
private:
    ListNode <T>* node;
};

template <typename T>
class List {
public:
    using value_type        = T;
    using pointer           = T*;
    using const_ponter      = T const*;
    using reference         = T&;
    using const_reference   = T const&;
    using iterator          = ListIterator<T>;
    using const_iterator    = ListConstIterator<T>;

//Task 4.2

//default constructor:

List(): //not sure I get initialiser lists
    size_{0}, 
    first_{nullptr}, 
    last_{nullptr} 
    {}
    
bool empty() const {
    return size_ == 0;
}
        
std::size_t size() const {
    return size_;
}

//Task 4.3

void push_front(T const& value) {
    ListNode<T>* node = new ListNode<T>{value, nullptr, nullptr};     
    if (empty()) {
        first_ = node;
        last_ = node;
    } 
    else {
        node->next = first_;
        first_->prev = node;
        first_ = node;
    }
    ++size_;
}

void push_back(T const& value) {
    ListNode<T>* node = new ListNode<T>{value, nullptr, nullptr};
    if (empty()) {
        first_ = node;
        last_ = node;
    }
    else {
        node->prev = last_;
        last_->next = node;
        last_ = node;
    }
    ++size_;
}

void pop_front() {
    if (empty()) {
        //do nothing
    }
    else if (size() == 1) {
        //turn into empty list
        delete first_;
        first_ = nullptr;
        last_ = first_;
        --size_;
    }
    else {
        auto temp = first_->next;
        delete first_;
        first_ = temp;
        first_->prev = nullptr;
        --size_;
    }
}


void pop_back() {
    if (empty()) {
        //do nothing
    }
    else if (size() == 1) {
        //turn into empty list
        delete first_;
        first_ = nullptr;
        last_ = first_;
        --size_;
    }
    else {
        auto temp = last_->prev;
        delete last_;
        temp->next = nullptr;
        last_ = temp;
        --size_; 
    }
}

T front() const{
    return first_->value;
}

T back() const{
    return last_->value;
}


private:
    std::size_t size_;
    ListNode<T>* first_;
    ListNode<T>* last_;

};
# endif // # define BUW_LIST_HPP