//
//  main.cpp
//  linked_list
//
//  Created by Сергей Петров on 26/10/2018.
//  Copyright © 2018 SergioPetrovx. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
class List
{
    
private:
    class Node
    {
    public:
        Node(const T& data, Node* n = NULL):ex(data),next(n){}
        T ex;
        Node* next;
    };
    
    Node* root;
    int length;
public:
    List() : root(NULL), length(0){}
    
    void add(const T& data)
    {
        if (root == 0)
            root = new Node(data);
        else
        {
            Node* cur;
            for(cur=root;cur->next;cur=cur->next){}
            cur->next=new Node(data);
        }
        length++;
    }
    
//    void delete_root()
//    {
//        root = root->next;
//    }
    
    T& operator[](int index)
    {
        Node *curr = root;
        while (curr && index-- > 0)
            curr = curr->next;
        if (curr)
            return curr->ex;
        else
            throw "Out of range";
        
    }
    
    void Tsort()
    {
        int left = 0, right = length - 1;
            
    }
    
    void print()
    {
        for (int i = 0; i < length-1; i++)
            cout << (*this)[i];
    }
    
};

int main(int argc, const char * argv[]) {
    
    List<int> l;
    l.add(4);
    l.add(8);
    l.add(5);
    l.add(1);
    l.add(2);
    l.add(5);
    l.add(8);
    l.Tsort();
    l.print();
    return 0;
}
