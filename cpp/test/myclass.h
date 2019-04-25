//
//  myclass.h
//  cpp_staff
//
//  Created by Сергей Петров on 31/03/2019.
//  Copyright © 2019 SergioPetrovx. All rights reserved.
//

#ifndef myclass_h
#define myclass_h
#include <vector>

template <typename T>
class comparator {
    T first, second;
public:
    comparator(T a1, T a2)
    {
        first = a1;
        second = a2;
    }
    
    bool compare()
    {
        return first < second;
    }
};

template <typename T>
class map
{
private:
    
    struct node
    {
        int key;
        node* left;
        node* right;
        node* parent;
    };
    
    node* root;
    
    class iterator
    {
        iterator()
        {
            
        }
        
    };
    
public:
    map()
    {
        
    }
    
    
    
    T& get_max_elem()
    {
        
    }
};


#endif /* myclass_h */
