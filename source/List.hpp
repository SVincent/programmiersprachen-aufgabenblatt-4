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

//Task 4.5
template <typename T>
class ListIterator {
public:
    using Self              = ListIterator <T>;

    using value_type        = T;
    using pointer           = T*;
    using reference         = T&;
    using difference_type   = ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;

//constructors
ListIterator():
    node{nullptr}
    {}

ListIterator(ListNode <T>* n):
    node{n}
    {}

//methods
reference operator*() const { //not a multiplication operator, but dereferencing
    return node->value;
}

pointer operator->() const {
    return &(node->value);
}

Self& operator++() { //pre-increment
    node = node->next; 
    return *this;
}

Self operator++(int) { //post-increment
    Self current = *this;
    ++(*this);
    return current;

}

//helper function: getNode
ListNode<T>* getNode() const{
    return node;
}

bool operator==(Self const& x) const {
    return node == x.getNode();
}

bool operator!=(Self const& x) const {
    return node != x.getNode();
}

Self next() const {
    if (node) {
        return ListIterator(node->next);
    }
    else {
        return ListIterator(nullptr);
    }
}

private:
// The Node the iterator is pointing to
    ListNode <T>* node;
};

template <typename T>
class ListConstIterator {
public:
//what are we supposed to implement here?
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

//constructor:

List(): //not sure I get initialiser lists
    size_{0}, 
    first_{nullptr}, 
    last_{nullptr} 
    {}

//Task 4.8: copy constructor
List(List<T> const& list): //deep copy, shallow not useful for lists
    size_{0},
    first_{nullptr},
    last_{nullptr}
    {
        for (auto c = list.begin(); c!=nullptr; ++c) {
            push_back(*c);
        }
    }
    
//destructor:   - Task 4.4
~List() {
    clear();
}

//methods

bool empty() const {
    return size_ == 0;
}
        
std::size_t size() const {
    return size_;
}

//Task 4.13
List(List<T>&& rhs) : //rhs: right hand side - rvalue
    size_(rhs.size()), //(moves size_ from rhs into the list)
    first_(rhs.first_),
    last_(rhs.last_) {
    rhs.size_= 0;   //clean up rhs
    rhs.first_ = nullptr;
    rhs.last_ = nullptr;
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

//Task 4.4
void clear() {
    while (!empty()) {
        pop_front();
    }             
}

//Task 4.5
iterator begin () const {//iterator: using
    return iterator(first_);   
}

iterator end () const {
    return iterator();
} 

//Task 4.9
void insert (ListIterator<T> const& position, T const& value) {
    auto n = position.getNode();
    if (n->prev != nullptr) { //if the old node at the position needs to be moved
        ListNode <T>* insertnode = new ListNode<T> {value, n->prev, n}; 
        n->prev->next = insertnode; 
        n->prev = insertnode;
        ++size_;
    }
    else if (n->prev == nullptr) { //if we want to insert at the beginning
        push_front(value);
    }
    else { //empty list
        push_back(value);
    }
}

//Task 4.10
void reverse() { //reverse list by switching first_ and last_, as well as next and prev for all nodes
    ListNode<T>* current = new ListNode<T>;
    current = first_;
    ListNode<T>* helper = new ListNode<T>();
    while(current != nullptr) {
        helper = current->next;
        current->next = current->prev;
        current->prev = helper;
        if (helper == nullptr) { 
            last_ = first_;
            first_ = current;
        } 
        current = helper;
    }
           
}

private:
    std::size_t size_;
    ListNode<T>* first_;
    ListNode<T>* last_;

};

//Task 4.7
template <typename T>
bool operator==(List<T> const& xs, List<T> const& ys) { //true if two lists have the same content
    //if the two lists aren't of the same length, they can't be the same
    if (xs.size() != ys.size()) {
        return false;
    }
    //if the two lists have the same length, we need to iterate over the contents
    else {
        ListIterator<T> X = xs.begin();
        ListIterator<T> Y = ys.begin();
        while (X != xs.end()) {
            //if a single element of the two lists is different, we know the lists are different
            if (*X != *Y) {
                return false;
            }
            else {
                ++X;
                ++Y;
            }    
        }
        //if we reach the end of the list, we know they are the same
        return true;
    }
}

template <typename T>
bool operator!=(List<T> const& xs, List<T> const& ys) {
    return !(xs==ys);
}

//Task 4.10
template <typename T>
List<T> reverse(List<T>const& xs) {
    List<T> new_list(xs);
    new_list.reverse();
    return new_list;
}

# endif // # define BUW_LIST_HPP