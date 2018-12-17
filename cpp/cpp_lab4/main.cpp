//
//  main.cpp
//  cpp_lab4
//
//  Created by Сергей Петров on 30/11/2018.
//  Copyright © 2018 SergioPetrovx. All rights reserved.
//

#include <algorithm>
#include <iostream>
#include <cstdlib>

using namespace std;

template <class T> class List {
    class Node {
    public:
        T data;
        Node *prev, *next;
        Node(const T &data_, Node *prev_ = 0, Node *next_ = 0)
        : data(data_), prev(prev_), next(next_) {}
    };
    
    Node *root, *last;
    
public:
    List();
    void push(const T &data);
    
    T& operator[](int i);
    
    class iterator {
        Node *node;
        
    public:
        typedef int difference_type;
        typedef T value_type;
        typedef T &reference;
        typedef T *pointer;
        typedef std::random_access_iterator_tag iterator_category;
        
        iterator(Node *n);
        
        iterator operator+(int index);
        
        iterator operator-(int index);
        
        bool operator<(const iterator &it);
        
        iterator &operator++();
        
        iterator &operator--();
        
        bool operator!=(const iterator &it);
        bool operator==(const iterator &it);
        
        // necessary for libc++ library
        iterator operator+=(int);
        bool operator>(const iterator&);
        bool operator>=(const iterator&);
        //
        
        int operator-(const iterator &n);
        
        T& operator*() { return node->data; }
        
        T *operator->() { return &node->data; }
    };
    
    iterator begin() ;
    
    iterator end() ;};

template <typename T> void print(List<T> l) {
    for (auto i : l) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    List<int> l;
    srand(42);
    for (int i = 0; i < 10; i++) {
        l.push(9 - i);
    }
    print(l);
    std::sort(l.begin(), l.end());
    print(l);
    for(int i=0;i<10;i++){
        l[i] = rand()%1000;
    }
    print(l);
    std::sort(l.begin(), l.end());
    print(l);
    return 0;
}

template <class T>
List<T>::List() : root(NULL), last(NULL) {}


template <class T>
void List<T>::push(const T& data)
{
    Node *new_node = new Node(data);
    if (last)
    {
        new_node->prev = last->prev;
        last->prev->next = new_node;
        new_node->next = last;
        last->prev = new_node;
    }
    else
    {
        last = new Node(T(INT_MIN));
        root = new_node;
        root->next = last;
        last->prev = root;
    }
}


template <class T>
T& List<T>::operator[](int i)
{
    Node *curr = root;
    while (i-- > 0)
        curr = curr->next;
    return curr->data;
}


template<class T>
List<T>::iterator::iterator(Node *n) : node(n) {}


template <class T>
typename List<T>::iterator List<T>::iterator::operator+(int index)
{
    Node *curr = node;
    while (index-- > 0)
        curr = curr->next;
    return iterator(curr);
}


template <class T>
typename List<T>::iterator List<T>::iterator::operator+=(int t)
{
    while (t-- > 0)
        node = node->next;
    return *this;
}


template <class T>
typename List<T>::iterator List<T>::iterator::operator-(int index)
{
    Node *curr = node;
    while (index-- > 0)
        curr = curr->prev;
    return iterator(curr);
}


template <class T>
bool List<T>::iterator::operator<(const iterator &it)
{
    return node->data < it.node->data;
}


template <class T>
bool List<T>::iterator::operator>(const iterator &it)
{
    return node->data > it.node->data;
}


template <class T>
bool List<T>::iterator::operator>=(const iterator &it)
{
    return node->data >= it.node->data;
}


template <class T>
typename List<T>::iterator& List<T>::iterator::operator++()
{
    node = (node) ? node->next : node;
    return *this;
}


template <class T>
typename List<T>::iterator& List<T>::iterator::operator--()
{
    node = (node) ? node->prev : node;
    return *this;
}


template <class T>
bool List<T>::iterator::operator!=(const iterator &it)
{
    return node->data != it.node->data;
}


template <class T>
bool List<T>::iterator::operator==(const iterator &it)
{
    return node->data == it.node->data;
}


template <class T>
int List<T>::iterator::operator-(const iterator &n)
{
    Node *curr_r = node;
    Node *curr_l = n.node;
    int count = 0;
    count = 0;
    while (curr_l != curr_r && curr_l && curr_r)
    {
        count++;
        curr_l = curr_l->next;
    }
    return count;
}


template <class T>
typename List<T>::iterator List<T>::begin()
{
    return iterator(root);
}


template <class T>
typename List<T>::iterator List<T>::end()
{
    return iterator(last);
}
