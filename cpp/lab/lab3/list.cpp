//
//  list.cpp
//  cpp_lab3
//
//  Created by e1nfalt on 02/11/2018.
//  Copyright © 2018 SergioPetrovx. All rights reserved.
//

#ifndef list_cpp
#define list_cpp

#include "list.h"
#include <iostream>

template<class T>
List<T>::Node::Node(T data_) : data(data_), next(NULL), prev(NULL) {}

template<class T>
bool List<T>::Node::operator<=(Node& other)
{
    return data <= other.data;
}

template<class T>
bool List<T>::Node::operator<(Node &other)
{
    return data < other.data;
}

template<class T>
List<T>::List() : root(NULL), length(0) {}

template<class T>
List<T>::~List()
{
    Node* curr = root;
    while (curr)
    {
        Node *t = curr->next;
        delete curr;
        curr = t;
    }
    root = NULL;
    length = 0;
}

template<class T>
void List<T>::push_back(T data_)
{
    Node *new_node = new Node(data_);
    if (length == 0)
        root = new_node;
    else
    {
        Node* curr = root;
        while (curr->next)
            curr = curr->next;
        new_node->prev = curr;
        curr->next = new_node;
    }
    length++;
}

template<class T>
void List<T>::sort()
{
    root = MergeSort(root);
    Node* curr_elem = root->next;
    Node* prev_elem = root;
    while (curr_elem)
    {
        curr_elem->prev = prev_elem;
        prev_elem = curr_elem;
        curr_elem = curr_elem->next;
    }
}

template<class T>
typename List<T>::Node& List<T>::operator[](unsigned long index)
{
    List<T>::Node *curr = root;
    while ((index--) > 0 && curr)
        curr = curr->next;
    return *curr;
}

template<class T>
typename List<T>::Node* List<T>::mergeLists(typename List<T>::Node* list1, typename List<T>::Node* list2)
{
    List<T>::Node* new_root;
    if (*list1 < *list2)
    {
        new_root = list1;
        list1=list1->next;
    }
    else
    {
        new_root = list2;
        list2=list2->next;
    }
    List<T>::Node* tmp = new_root;
    while (list1 && list2)
    {
        if (*list1 < *list2)
        {
            tmp->next = list1;
            list1->prev = tmp;
            tmp = list1;
            list1 = list1->next;
        }
        else
        {
            tmp->next = list2;
            list2->prev = tmp;
            tmp = list2;
            list2 = list2->next;
        }
    }
    tmp->next = list1 ? list1 : list2;
    return new_root;
}

template<class T>
typename List<T>::Node* List<T>::MergeSort(typename List<T>::Node *start_)
{
    if (!start_ || !start_->next)
        return start_;
    typename List<T>::Node* first_half_start = start_;
    typename List<T>::Node* second_half_start = start_->next;
    while (second_half_start && second_half_start->next)
    {
        second_half_start = second_half_start->next->next;
        start_ = start_->next;
    }
    second_half_start = start_->next;
    start_->next = 0;
    start_->prev = 0;
    first_half_start = MergeSort(first_half_start);
    second_half_start = MergeSort(second_half_start);
    return mergeLists(first_half_start, second_half_start);
}


#endif
