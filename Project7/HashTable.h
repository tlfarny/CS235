#pragma once
#include "LinkedList.h"

using namespace std;

template <typename ItemType>

class HashSet {
    
public:
    
    HashSet(){
        LinkedList<ItemType>* table;
        size=0;
        capacity=0;
        table = new LinkedList<ItemType>[size];
        table = NULL;
    }
    
    ~HashSet(){
        delete [] table;
    }
    
    LinkedList<ItemType>* table;
    int capacity;
    int size;
    
    
    void add(const ItemType& item) {
        
    }
    
    void remove(const ItemType& item) {
        /*
         code
         */
    }
    
    bool find(const ItemType& item) {
        
        return false;
    }
    
    void print(){
        
    }
    
    unsigned hashCode( const string& s ) {
        '
        
    }
    
    
};