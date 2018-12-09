//
//  list.hpp
//  cpp_lab3
//
//  Created by e1nfalt on 02/11/2018.
//  Copyright © 2018 SergioPetrovx. All rights reserved.
//

#ifndef list_hpp
#define list_hpp

#include <cstdlib>

template<class T>
class List
{
private:
    
    class Node
    {
    public:
        T data;
        Node* next;
        Node* prev;
        
        Node(T = NULL);
        bool operator<=(Node&);
        bool operator<(Node&);
    };
    
    Node* root;
    Node* end;
    int length;
public:
    
    List();
    ~List();
    void push_back(T);
    void sort();
    Node& operator[](unsigned long);
    //Node* GetElemOnIndex(unsigned long);
    Node* MergeSort(Node*);
    Node* mergeLists(Node*, Node*);
};

#include "list.cpp"

#endif /* list_hpp */
